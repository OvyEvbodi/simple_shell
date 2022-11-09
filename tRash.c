#include "main.h"

/**
 * main - Entry point of program.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *buffer, **arr_tokens, *token_zero, *cmd_full_path;
	char **env = environ;
	size_t buff_size;

	while (1)
	{
		buffer = NULL;
		buff_size = 0;
		write(1, "tRash-->$ ", 10);

		if (_getline(&buffer, &buff_size, stdin) == -1)
			eof(buffer);
		if (buffer[0] == '\n')
		{
			free(buffer);
			continue;
		}

		token_zero = get_tokens(buffer, &arr_tokens);
		if (builtins(arr_tokens, env, buffer))
			continue;

		cmd_full_path = _getcmd(token_zero, arr_tokens, env);
		if (!cmd_full_path)
		{
			write(2, "not found\n", 10);
			free(buffer);
			free(arr_tokens);
			continue;
		}

		exec_cmd(buffer, arr_tokens, cmd_full_path, env);
	}
	return (0);
}

