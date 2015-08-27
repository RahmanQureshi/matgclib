function rc = move(axis, speed, displacement, blocking)
	con = GOpen('10.10.1.21 -d');
	countspermm = 629.8;
	GCommand(con, 'SH');
	GCommand(con, strcat('SP', axis, '=', num2str(round(speed*countspermm))));
	GCommand(con, strcat('IP', axis, '=', num2str(round(displacement*countspermm))));
	pause(0.2);
	while strcmp(blocking, 'block')
		speed = str2num(strtrim(strtok(GCommand(con, strcat('TV', axis)), ':')));
		if speed == 0
			break
		end
	end
	GClose(con);
	rc = 0;