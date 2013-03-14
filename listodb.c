#include <git2.h>
#include <stdio.h>

int foreach_cb(const git_oid* oid, void *data) {
	char out[41];
	out[40] = '\0';
	
	git_oid_fmt(out, oid);
	printf("%s\n", out);
	
	return 0;
}

int show_all_odb(git_repository* repo) {
  static git_odb* odb;
  
  git_repository_odb(&odb, repo);
  git_odb_foreach(odb, foreach_cb, NULL);
}

int main() {
  git_repository* repo;
  
  git_repository_open(&repo, ".");
  return show_all_odb(repo);
}