#include <stdio.h>
#include <git2.h>

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

int main(int argc, char** argv) {
  git_repository* repo;
  
  if (argc < 2) {
    git_repository_open(&repo, ".");
  } else {
    git_repository_open(&repo, argv[1]);
  }
  return revwalk_from_head(repo);
}
