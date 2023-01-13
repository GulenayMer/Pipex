# Pipex

Creating a simple pipeline mechanism for inter-process communication.

Executed as 'file1 cmd1 cmd2 file2' && behaves exactly as the shell command ' $> < file1 cmd1 | cmd2 > file2 '

No memory leaks are allowed.
