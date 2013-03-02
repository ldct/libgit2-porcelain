#include <git2.h>
#include <stdio.h>

int revwalk_from_head(git_repository* repo) {
  git_revwalk *walk;
  git_commit *wcommit;
  git_oid oid;

  git_revwalk_new(&walk, repo);
  
  char out[41];
  out[40] = '\0';

  git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL);

  git_revwalk_push_head(walk);
  while ((git_revwalk_next(&oid, walk)) == 0) {
    git_commit_lookup(&wcommit, repo, &oid);
    git_oid_fmt(out, &oid);
    printf("%s\n", out);
    git_commit_free(wcommit);
  }
  git_revwalk_free(walk);

  return 0;
}

int main() {
  git_repository* repo;
  
  git_repository_open(&repo, ".");
  return revwalk_from_head(repo);
}
