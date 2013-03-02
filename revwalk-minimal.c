#include <stdio.h>
#include <git2.h>

int revwalk_from_head(git_repository* repo) {
  git_revwalk *walk;
  git_oid w_oid;
  
  char out[41];
  out[40] = '\0';

  git_revwalk_new(&walk, repo);
  git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL);
  
  git_revwalk_push_head(walk);
  while ((git_revwalk_next(&w_oid, walk)) == 0) {
    git_oid_fmt(out, &w_oid);
    printf("%s\n", out);
  }
  git_revwalk_free(walk);

  return 0;
}

int main() {
  git_repository* repo;
  
  git_repository_open(&repo, ".");
  return revwalk_from_head(repo);
}
