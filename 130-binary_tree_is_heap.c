#include "binary_trees.h"
/**
 * heap_height_for_is_heap - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the height.
 * Return: If tree is NULL, your function must return 0, else return height.
 */
size_t heap_height_for_is_heap(const binary_tree_t *tree)
{
	int height_left, height_right;

	if (tree == NULL)
		return (0);
	if (tree->left == NULL)
		height_left = 0;
	else
		height_left = 1 + heap_height_for_is_heap(tree->left);
	if (tree->right == NULL)
		height_right = 0;
	else
		height_right = 1 + heap_height_for_is_heap(tree->right);
	return ((height_left > height_right) ? height_left : height_right);
}
/**
 * do_complete_recursive_for_is - Checks if a binary tree is complete.
 * @tree: A pointer to the root node of the tree to traverse.
 * @depth: tree depth.
 * @level: recursion level.
 * @is_left_finish: flag the finish.
 * Return: If the tree is NULL or not complete fail, 0.
 *         Otherwise, 1.
 */
int do_complete_recursive_for_is(const binary_tree_t *tree, int depth,
		int level, int *is_left_finish)
{
	int left_res, right_res;

	if (depth == level + 1)
	{
		if (*is_left_finish == 0)
		{
			if (tree->left != NULL && tree->right != NULL)
			{
				*is_left_finish = 0;
				return (1);
			}
			if ((tree->left != NULL && tree->right == NULL) ||
					(tree->left == NULL && tree->right == NULL))
			{
				*is_left_finish = 1;
				return (1);
			}
			if (tree->left == NULL && tree->right != NULL)
			{
				*is_left_finish = 1;
				return (0);
			}
		}
		else
		{
			if (tree->left == NULL && tree->right == NULL)
				return (1);
			else
				return (0);
		}
	}
	if (tree->left == NULL && tree->right == NULL)
		return (level == depth ? 1 : 0);
	if (tree->left == NULL || tree->right == NULL)
		return (0);
	left_res = do_complete_recursive_for_is(tree->left, depth,
			level + 1, is_left_finish);
	right_res = do_complete_recursive_for_is(tree->right, depth,
			level + 1, is_left_finish);
	return (left_res && right_res);
}
/**
 * heap_is_complete - Checks if a binary tree is complete.
 * @tree: A pointer to the root node of the tree to traverse.
 *
 * Return: If the tree is NULL or not complete, 0.
 *         Otherwise, 1.
 * Description: Upon malloc failure, exits with a status code of 1.
 */
int heap_is_complete(const binary_tree_t *tree)
{
	int is_left_finish = 0;

	if (tree == NULL)
		return (0);
	return (do_complete_recursive_for_is(tree, heap_height_for_is_heap(tree),
				0, &is_left_finish));
}
/**
 * check_heap - checks if parent has a greater value than its childs
 *
 * @tree: pointer to the node
 * Return: 1 if parent has a greater value, 0 otherwise
 */
int check_heap(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (1);

	if (tree->n > tree->parent->n)
		return (0);

	return (check_heap(tree->left) && check_heap(tree->right));
}
/**
 * binary_tree_is_heap - checks if an binary tree is valid Max Binary Heap
 * @tree: pointer to the root of the tree
 * Return: 1 if tree is a Max Binary Heap, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	int res;

	if (tree == NULL)
		return (0);

	res = heap_is_complete(tree);
	if (res == 0)
		return (0);

	return (check_heap(tree->left) && check_heap(tree->right));
}
