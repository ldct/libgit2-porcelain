#include <git2.h>
#include <stdio.h>

int diff_print_cb(
  const git_diff_delta *delta,
  const git_diff_range *range,
  char line_origin, /**< GIT_DIFF_LINE_... value from above */
  const char *content,
  size_t content_len,
  void *payload)
{
  printf("%s", content);
  return 0;
}

void print_diff(git_diff_list* diff)
{
  git_diff_print_patch(diff, diff_print_cb, NULL);
}

//diffs workdir and index - ie unstaged changes
int diff(git_repository* repo) {
  git_diff_list* diff;

  git_index* index;  

  git_reference* ref_head;
  git_commit* head;
  git_tree* head_tree;


  git_repository_index(&index, repo);
  git_index_read(index);

  git_repository_head(&ref_head, repo);
  git_reference_peel((git_object**) &head, ref_head, GIT_OBJ_COMMIT);
  git_commit_tree(&head_tree, head);
	git_diff_index_to_workdir(&diff, repo, index, NULL);

  print_diff(diff);

  return 0;
}

int main() {
  git_repository* repo;
  
  git_repository_open(&repo, ".");
  return diff(repo);
}
