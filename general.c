#include <git2.h>
#include <stdio.h>

#include "libcore.c"

git_repository* repo;

//TODO: advance HEAD, link to parent commit
int stage_and_commit(char* filename, char* message) { //only works for a single file

  git_oid tree_oid, commit_oid;
  git_tree *tree;
  git_signature *signature;
  git_index *index;

  git_repository_index(&index, repo);
  git_index_add_bypath(index, filename);
  git_index_write(index);

  git_index_write_tree(&tree_oid, index);
  git_index_free(index);
    
  git_tree_lookup(&tree, repo, &tree_oid);
  
  git_signature_new(&signature, "Li Xuanji", "xuanji@gmail.com", 1323847743, 60);
  git_commit_create_v(
    &commit_oid,
    repo,
    "HEAD",
    signature,
    signature,
    NULL,
    message,
    tree,
    0);

  git_tree_free(tree);
  git_signature_free(signature);

  return 0;
}

int listrefs() {
  git_strarray ref_list;
  git_reference_list(&ref_list, repo, GIT_REF_LISTALL);

  const char *refname;
  git_reference *ref;
  
  char out[41];
  out[40] = '\0';
  
  int i;

  for (i = 0; i < ref_list.count; ++i) {
    refname = ref_list.strings[i];
    git_reference_lookup(&ref, repo, refname);

    switch (git_reference_type(ref)) {
    case GIT_REF_OID:
      git_oid_fmt(out, git_reference_target(ref));
      printf("%s [%s]\n", refname, out);
      break;
    case GIT_REF_SYMBOLIC:
      printf("%s => %s\n", refname, git_reference_symbolic_target(ref));
      break;
    default:
      fprintf(stderr, "Unexpected reference type\n");
      exit(1);
    }
  }

  git_strarray_free(&ref_list);
}

int revwalk_from_head(git_repository* repo) {
  git_revwalk *walk;
  git_commit *w_commit;
  git_oid w_oid;
  
  char out[41];
  out[40] = '\0';

  git_revwalk_new(&walk, repo);
  git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL);
  
  git_revwalk_push_head(walk);
  while ((git_revwalk_next(&w_oid, walk)) == 0) {
    git_oid_fmt(out, &w_oid);
    git_commit_lookup(&w_commit, repo, &w_oid);
    printf("%s %s", out, git_commit_message(w_commit));
    git_commit_free(w_commit);
  }
  git_revwalk_free(walk);

  return 0;
}

int main() {
  
  git_repository_init(&repo, "zit", 0);

  touch("zit/readme", "Zit \n --- git for zombieis");
  stage_and_commit("readme", "Initial commit\n\0");

  touch("zit/TODO", "- Make project logo \n- Watch Friends");
  stage_and_commit("TODO", "TODO\n\0");

  revwalk_from_head(repo);
  
  listrefs();
  
  return 0;
}
