#include <git2.h>
#include <stdio.h>

int treewalk_cb(const char *root, const git_tree_entry *entry, void *payload) {
	printf("%s\n", git_tree_entry_name(entry));
	return 0;
}

int show_index(git_repository* repo) {
  git_oid index_tree_oid;
  git_tree *index_tree;
  git_index *index;
  
  int ct;
  
  git_repository_index(&index, repo);
  git_index_read(index);
  git_index_write_tree(&index_tree_oid, index);
  git_index_free(index);
    
  git_tree_lookup(&index_tree, repo, &index_tree_oid);
  
  git_tree_walk(index_tree, GIT_TREEWALK_PRE, treewalk_cb, &ct);
}

int main(int argc, char** argv) {
  git_repository* repo;
  
  if (argc < 2) {
    git_repository_open(&repo, ".");
  } else {
    git_repository_open(&repo, argv[1]);
  }
  return show_index(repo);
}
