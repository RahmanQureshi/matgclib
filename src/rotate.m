function rc = rotate(degrees_per_second, degrees, blocking)
	con = GOpen('10.10.1.21 -d');
	counts_per_degree = 889;
	GCommand(con, 'SH');
	GCommand(con, strcat('SPW', '=', num2str(round(degrees_per_second*counts_per_degree))));
	GCommand(con, strcat('IPW', '=', num2str(round(degrees*counts_per_degree))));
	while strcmp(blocking, 'block')
		speed = str2num(strtrim(strtok(GCommand(con, strcat('TVW')), ':')));
		if speed == 0
			break
		end
	end
	GClose(con);
	rc = 0;