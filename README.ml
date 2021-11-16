Subject: Computer systems design theory
Student: Oleksandr Papish, CE-48
Student number: 12
Task by student: HW interface - I2C, Game - sea battle game, Data driven format - BINARY

How to build project:
	Project contains 3 solution: 
		a) UI(SeaBattle); 
		b) UART to I2C bridge(SeaBattleBridge); 
		c) Game server side(SeaBattleServerSide);
	
	Firstly, you must connect Arduino and Psoc to PC. Then connect Arduino GND to Psoc GND, Arduino SCL to Psoc P3[0], Arduino SDA to Psoc P3[1].
	Secondly, you must open SeaBattleBridge/SeaBattleBridge.ino in Arudino IDE and upload script to Arduino board.
	Thirdly, you must open SeaBattleServerSideWorkspace/SeaBattleServerSideWorkspace.cywrk in PsocCreator and upload this to Psoc board.
	Fourthly, you must open SeaBattle/SeaBattle.sln, select communication.h file and change DEVICE constant to Arduino COM Port.
	After that you can run the project and start playing.

	Detailed information is located in HowToRun.pdf

How to build and run tests:
	Project contains 4 tests:
		a) Unit tests;
		b) Integration tests;
		c) Automation tests;
		d) Manual tests;

	Detailed information is located in HowToRun.pdf