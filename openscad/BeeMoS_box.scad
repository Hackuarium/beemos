	  boardLength=127;      // including USB port protruding 
	  boardWidth=32;
	  boardHeight=6;
	  wallThickness=3;      // including USB port protruding
	  IRLength=5;         // individual IR emitter/receiver measurements including IC legs
	  IRWidth=4;          // 
	  IRHeight=2;
	  xSpaceBetweenGates=13;
	  ySpaceBetweenGates=9;
	  

	 module get_board_vol(){  
	 //Estimates the volume of the cuboid needed to fit the board in red (taking max values for height so that the USB port has enough space), space for IR sensors (bottom of board) are in yellow 
	
	      color("red")
	      cube([boardLength,boardWidth,boardHeight],center=true);
	      // make 8 yellow IR sensors
	      translate([-32,-2.5,0]) // positioning of the 8 gates
	      get_8_gates();
	      translate([-32,-2.5-ySpaceBetweenGates,0]) // positioning of the 8 gates
	      get_8_gates();	      

	      }
	module get_8_gates(){
	        for (i=[0:7])
	      translate([boardLength/2-0.5-xSpaceBetweenGates*i,boardWidth/2-0.5,boardHeight/2+0.5])
	      color("yellow")
	      cube([IRLength,IRWidth,IRHeight],center=true);
	    }
	
	get_board_vol();
translate([-4,0,0]){
   difference(){
   color("orange")
	translate([0,0,20])
	cube([boardLength+2+8,boardWidth+2,8],center=true);
   color("blue")
	translate([0,0,22])
	cube([boardLength+8,boardWidth,7],center=true);
	}
}