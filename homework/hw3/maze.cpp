bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec) // base case // maze was solved 
		return true; 

	maze[sr][sc] = '~'; //marks the location as visited
	
	if (maze[sr + 1][sc] == '.') //south
	{
		if (pathExists(maze, sr + 1, sc, er, ec) == true)
			return true; 
	}
	if (maze[sr][sc + 1] == '.') //east
	{
		if (pathExists(maze, sr, sc + 1, er, ec) == true)
			return true; 
	}
	if (maze[sr - 1][sc] == '.') //north
	{
		if (pathExists(maze, sr - 1, sc, er, ec) == true)
			return true; 
	}
	if (maze[sr][sc - 1] == '.') //west
	{
		if (pathExists(maze, sr, sc - 1, er, ec) == true)
			return true;
	}

	return false; 
}

