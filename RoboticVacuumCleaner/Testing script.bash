#!/bin/bash

test_num=0
REPORT_FILE=a1_n9801154_test_report.txt

echo "Remember to do these two commands before running this script:
export COLUMNS
export LINES
"
echo "Test run starting at $(date)" >>${REPORT_FILE}

#==============================================================================
#	Operations available in the Vacuum simulation.
#==============================================================================
function move_vacuum () {
	printf "v${1},${2},${3} " 
}

function move_dust () {
	printf "d${1},${2} " 
}

function move_slime () {
	printf "s${1},${2} " 
}

function move_trash () {
	printf "t${1},${2} " 
}

function set_timeout () {
	printf "o${1} "
}

function set_delay () {
	printf "m${1} "
}

function pause_resume () {
	printf "p "
}

function reset () {
	printf "r${1} "
}

function left () {
	printf "j "
}

function right () {
	printf "l "
}

function up () {
	printf "i "
}

function down () {
	printf "k "
}

function batt_lvl () {
	printf "y${1} "
}

function rtb () {
	printf "b "
}

function load () {
	printf "w${1} "
}

function reset () {
	printf "r${1},${2},${3} "
}

function quit () {
	printf "q "
}

function quit () {
	printf "? "
}

function loop () {
	if (( $# >= 1 )) && (( $1 > 0 )) 
	then
		for (( i = 0; i < $1; i++ ))
		do
			printf " "
		done
	else
		printf " "
	fi
}

function enter () {
	printf "${1} "
}

#========================================================================
#	Run a single test.
#========================================================================	

function run_test () {
	(( test_num ++ ))
	echo "Test    : ${test_num}"
	echo "Category: ${category}"
	echo "Details : ${details}"
	echo "Expect  : ${expect}"
	
	read -p "Press r to run the test or s to skip..." run_or_skip
	
	if [ "${run_or_skip}" == "r" ]
	then
		echo ${cmd} | ./a1_n9801154
		read -p "Did the test pass or fail (p/f)? " result
		echo "Test ${test_num}: ${result}" >>${REPORT_FILE}
	fi
}

#==============================================================================
category="Setup vacuum"
details="Vacuum alone in center of terminal window."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible."

cmd=$(
	enter 0
	enter 0
	enter 0
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup 1 dust"
details="Vacuum and 1 piece of dust."
expect="Vacuum is displayed in centre; 1 piece of dust is visible; no overlap."

cmd=$(
	enter 0
	enter 0
	enter 1
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup 1 slime"
details="Vacuum and 1 piece of slime."
expect="Vacuum is displayed in centre; 1 piece of slime is visible; no overlap."

cmd=$(
	enter 0
	enter 1
	enter 0
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup 1 trash"
details="Vacuum and 1 piece of trash."
expect="Vacuum is displayed in centre; 1 piece of trash is visible; no overlap."

cmd=$(
	enter 1
	enter 0
	enter 0
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup max dust"
details="Vacuum and 1000 pieces of dust."
expect="Vacuum is displayed in centre; 1000 pieces of dust are visible; no overlap."

cmd=$(
	enter 0
	enter 0
	enter 1000
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup max slime"
details="Vacuum and 10 pieces of slime."
expect="Vacuum is displayed in centre; 10 pieces of slime are visible; no overlap."

cmd=$(
	enter 0
	enter 10
	enter 0
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup max trash"
details="Vacuum and 5 pieces of trash."
expect="Vacuum is displayed in centre; 5 pieces of trash are visible; no overlap."

cmd=$(
	enter 5
	enter 0
	enter 0
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup 1 of each type"
details="Vacuum, 1 piece of dust, 1 piece of slime and 1 piece of trash."
expect="Vacuum is displayed in centre; 1 piece of each type of rubbish is visible; no overlap."

cmd=$(
	enter 1
	enter 1
	enter 1
	set_timeout 3
)

run_test 
#==============================================================================
category="Setup 5 of each type"
details="Vacuum, 5 pieces of dust, 5 pieces of slime and 5 pieces of trash."
expect="Vacuum is displayed in centre; 5 pieces of each type of rubbish is visible; no overlap."

cmd=$(
	enter 5
	enter 5
	enter 5
	set_timeout 5
)

run_test 
#==============================================================================
category="Setup max of each type"
details="Vacuum, 1000 pieces of dust, 10 pieces of slime and 5 pieces of trash."
expect="Vacuum is displayed in centre; 1000 pieces of dust, 10 pieces of slime and 5 pieces of trash is visible; no overlap."

cmd=$(
	enter 5
	enter 10
	enter 1000
	set_timeout 5
)

run_test 
#==============================================================================
category="Do vacuum cheat"
details="Vacuum alone; placed in four corners of display, clockwise."
expect="Vacuum is displayed briefly in centre; no trash, slime or dust is visible; vacuum teleports in turn to [1,5], [w-6,5], [w-6,h-5], [1,h-5]."

(( LEFT = 1, TOP = 5, RIGHT = COLUMNS - 6, BOTTOM = LINES - 5 ))
		
cmd=$(
	enter 0
	enter 0
	enter 0
	set_timeout 5
	set_delay 1000
	move_vacuum ${LEFT} ${TOP} 0
	move_vacuum ${RIGHT} ${TOP} 0
	move_vacuum ${RIGHT} ${BOTTOM} 0
	move_vacuum ${LEFT} ${BOTTOM} 0
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacume alone; push device left."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum is pushed left until hitting the boarder wall."

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 1000
	set_timeout 5
	set_delay 10
	for (( i = 0; i < COLUMNS; i++ )) ; do left ; done
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacume alone; push device right."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum is pushed right until hitting the boarder wall."

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 1000
	set_timeout 5
	set_delay 10
	for (( i = 0; i < COLUMNS; i++ )) ; do right ; done
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacume alone; push device up."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum is pushed up until hitting the charging station."

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 1000
	set_timeout 4
	set_delay 10
	for (( i = 0; i < COLUMNS; i++ )) ; do up ; done
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacume alone; push device down."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum is pushed down until hitting the boarder wall."

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 1000
	set_timeout 4
	set_delay 10
	for (( i = 0; i < COLUMNS; i++ )) ; do down ; done
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacuum alone; device pushed left and right at bottom."
expect="Vacuum is displayed at bottom left corner; no trash, slime or dust is visible; vacuum is pushed right and left until hitting the wall."

(( LEFT = 1, BOTTOM = LINES - 5 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	move_vacuum ${LEFT} ${BOTTOM} 0
	set_delay 100
	set_timeout 8
	set_delay 3
	for (( i = 0; i < COLUMNS * 11 / 10; i++ )) ; do right ; done
	for (( i = 0; i < COLUMNS * 11 / 10; i++ )) ; do left ; done
	for (( i = 0; i < COLUMNS * 11 / 10; i++ )) ; do right ; done
	for (( i = 0; i < COLUMNS * 11 / 10; i++ )) ; do left ; done
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacuum alone; device pushed up and down at left."
expect="Vacuum is displayed at bottom left corner; no trash, slime or dust is visible; vacuum is pushed up and down until hitting the wall."

(( LEFT = 1, BOTTOM = LINES - 5 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	move_vacuum ${LEFT} ${BOTTOM} 0
	set_delay 100
	set_timeout 5
	set_delay 4
	for (( i = 0; i < LINES * 2; i++ )) ; do up ; done
	for (( i = 0; i < LINES * 2; i++ )) ; do down ; done
	for (( i = 0; i < LINES * 2; i++ )) ; do up ; done
	for (( i = 0; i < LINES * 2; i++ )) ; do down ; done
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacuum alone; run north-east and bounce."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum moves north-east and when it hits the wall it continues to turn at a random angle between +/- 30-60 degrees until it deflects away."

	(( VX = (COLUMNS/2)-(9/2), VY = (LINES/2)-(9/2), DIR = 360 - 45 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	move_vacuum ${VX} ${VY} ${DIR}
	set_delay 200
	set_timeout 3
	set_delay 5
	pause_resume
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacuum alone; run north-west and bounce."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum moves north-west and when it hits the wall it continues to turn at a random angle between +/- 30-60 degrees until it deflects away."

	(( VX = (COLUMNS/2)-(9/2), VY = (LINES/2)-(9/2), DIR = 270 - 45 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	move_vacuum ${VX} ${VY} ${DIR}
	set_delay 200
	set_timeout 3
	set_delay 5
	pause_resume
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacuum alone; run south-east and bounce."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum moves south-east and when it hits the wall it continues to turn at a random angle between +/- 30-60 degrees until it deflects away."

	(( VX = (COLUMNS/2)-(9/2), VY = (LINES/2)-(9/2), DIR = 90 - 45 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	move_vacuum ${VX} ${VY} ${DIR}
	set_delay 200
	set_timeout 3
	set_delay 5
	pause_resume
)

run_test
#==============================================================================
category="Update vacuum"
details="Vacuum alone; run south-west and bounce."
expect="Vacuum is displayed in centre; no trash, slime or dust is visible; vacuum moves south-west and when it hits the wall it continues to turn at a random angle between +/- 30-60 degrees until it deflects away."

	(( VX = (COLUMNS/2)-(9/2), VY = (LINES/2)-(9/2), DIR = 180 - 45 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	move_vacuum ${VX} ${VY} ${DIR}
	set_delay 200
	set_timeout 3
	set_delay 5
	pause_resume
)

run_test
#==============================================================================
category="Drop dust cheat"
details="Vacuum alone; 1 piece of dust is dropped in each of the four corners of display, clockwise."
expect="No dust, slime or trash is visible; 1 dust is dropped in each corner [1,5], [w-2,5], [w-2,h-5], [1,h-3]."

(( LEFT = 1, TOP = 5, RIGHT = COLUMNS - 2, BOTTOM = LINES - 3 ))
		
cmd=$(
	enter 0
	enter 0
	enter 0
	set_timeout 5
	set_delay 1000
	move_dust ${LEFT} ${TOP}
	move_dust ${RIGHT} ${TOP}
	move_dust ${RIGHT} ${BOTTOM}
	move_dust ${LEFT} ${BOTTOM}
)

run_test
#==============================================================================
category="Drop slime cheat"
details="Vacuum alone; 1 piece of slime is dropped in each of the four corners of display, clockwise."
expect="No dust, slime or trash is visible; 1 slime is dropped in each corner [1,5], [w-4,5], [w-4,h-5], [1,h-5]."

(( LEFT = 1, TOP = 5, RIGHT = COLUMNS - 4, BOTTOM = LINES - 5 ))
		
cmd=$(
	enter 0
	enter 0
	enter 0
	set_timeout 5
	set_delay 1000
	move_slime ${LEFT} ${TOP} 0
	move_slime ${RIGHT} ${TOP} 0
	move_slime ${RIGHT} ${BOTTOM} 0
	move_slime ${LEFT} ${BOTTOM} 0
)

run_test
#==============================================================================
category="Drop trash cheat"
details="Vacuum alone; 1 piece of trash is dropped in each of the four corners of display, clockwise."
expect="No dust, slime or trash is visible; 1 trash is dropped in each corner [1,5], [w-6,5], [w-6,h-5], [1,h-5]."

(( LEFT = 1, TOP = 5, RIGHT = COLUMNS - 6, BOTTOM = LINES - 5 ))
		
cmd=$(
	enter 0
	enter 0
	enter 0
	set_timeout 5
	set_delay 1000
	move_trash ${LEFT} ${TOP} 0
	move_trash ${RIGHT} ${TOP} 0
	move_trash ${RIGHT} ${BOTTOM} 0
	move_trash ${LEFT} ${BOTTOM} 0
)

run_test
#==============================================================================
category="Collision"
details="Vacuum passes vertically between two pieces of dust (near miss)."
expect="Vacuum is displayed in centre; two pieces of dust are below vacuum, one at either side; Vacuum runs between dust, just missing."

(( X = COLUMNS / 2, Y = LINES / 2, DX1 = X - 5, DY1 = Y + 10, DX2 = X + 5, DY2 = Y + 10 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_dust ${DX1} ${DY1}
	move_dust ${DX2} ${DY2}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum passes horizontally between two pieces of dust (near miss)."
expect="Vacuum is displayed in centre; two pieces of dust are to the left of the vacuum, one above, one below; Vacuum runs between dust, just missing."

(( X = COLUMNS / 2, Y = LINES / 2, DX1 = X - 20, DY1 = Y + 5, DX2 = X - 20, DY2 = Y - 5, VX = X-(9/2), VY = Y-(9/2), DIR = 180 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_vacuum ${VX} ${VY} ${DIR}
	move_dust ${DX1} ${DY1}
	move_dust ${DX2} ${DY2}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum passes vertically between two pieces of slime (near miss)."
expect="Vacuum is displayed in centre; two pieces of slime are below vacuum, one at either side; Vacuum runs between slime, just missing."

(( X = COLUMNS / 2, Y = LINES / 2, DX1 = X - 9, DY1 = Y + 10, DX2 = X + 5, DY2 = Y + 10 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_slime ${DX1} ${DY1}
	move_slime ${DX2} ${DY2}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum passes horizontally between two pieces of slime (near miss)."
expect="Vacuum is displayed in centre; two pieces of slime are to the left of the vacuum, one above, one below; Vacuum runs between slime, just missing."

(( X = COLUMNS / 2, Y = LINES / 2, DX1 = X - 20, DY1 = Y + 5, DX2 = X - 20, DY2 = Y - 9, VX = X-(9/2), VY = Y-(9/2), DIR = 180 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_vacuum ${VX} ${VY} ${DIR}
	move_slime ${DX1} ${DY1}
	move_slime ${DX2} ${DY2}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum passes vertically between two pieces of trash (near miss)."
expect="Vacuum is displayed in centre; two pieces of trash are below vacuum, one at either side; Vacuum runs between trash, just missing."

(( X = COLUMNS / 2, Y = LINES / 2, DX1 = X - 15, DY1 = Y + 5, DX2 = X + 5, DY2 = Y + 5 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_trash ${DX1} ${DY1}
	move_trash ${DX2} ${DY2}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum passes horizontally between two pieces of trash (near miss)."
expect="Vacuum is displayed in centre; two pieces of trash are to the left of the vacuum, one above, one below; Vacuum runs between trash, just missing."

(( X = COLUMNS / 2, Y = LINES / 2, DX1 = X - 20, DY1 = Y + 5, DX2 = X - 20, DY2 = Y - 10, VX = X-(9/2), VY = Y-(9/2), DIR = 180 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_vacuum ${VX} ${VY} ${DIR}
	move_trash ${DX1} ${DY1}
	move_trash ${DX2} ${DY2}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum moves north to collect 1 dust, 1 slime and 1 trash."
expect="Vacuum is displayed in bottom left corner; Vacuum is below 1 dust, 1 slime and 1 trash; Vacuum moves north and collides sequentially with 1 dust, 1 slime and 1 trash."

(( LEFT = 2, BOTTOM = LINES - 5, DY = (LINES / 2)+10, SY = (LINES / 2), TY = (LINES / 2)-10, DIR = 270 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_vacuum ${LEFT} ${BOTTOM} ${DIR}
	move_dust 6 ${DY}
	move_slime 4 ${SY}
	move_trash 1 ${TY}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum moves east to collect 1 dust, 1 slime and 1 trash."
expect="Vacuum is displayed in bottom left corner; Vacuum is to the west of 1 dust, 1 slime and 1 trash; Vacuum moves east and collides sequentially with 1 dust, 1 slime and 1 trash."

(( LEFT = 2, BOTTOM = LINES - 5, DX = LEFT+20, DY = BOTTOM-3, SX = LEFT+30, SY = BOTTOM-5, TX = LEFT+50, TY = BOTTOM-6, DIR = 0 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 5
	move_vacuum ${LEFT} ${BOTTOM} ${DIR}
	move_dust ${DX} ${DY}
	move_slime ${SX} ${SY}
	move_trash ${TX} ${TY}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum moves south to collect 1 dust, 1 slime and 1 trash."
expect="Vacuum is displayed in top left corner; Vacuum is above 1 dust, 1 slime and 1 trash; Vacuum moves south and collides sequentially with 1 dust, 1 slime and 1 trash."

(( LEFT = 2, TOP = 6, DY = (LINES / 2)-10, SY = (LINES / 2), TY = (LINES / 2)+10, DIR = 90 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 10
	move_vacuum ${LEFT} ${TOP} ${DIR}
	move_dust 6 ${DY}
	move_slime 4 ${SY}
	move_trash 1 ${TY}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Collision"
details="Vacuum moves west to collect 1 dust, 1 slime and 1 trash."
expect="Vacuum is displayed in bottom right corner; Vacuum is to the east of 1 dust, 1 slime and 1 trash; Vacuum moves west and collides sequentially with 1 dust, 1 slime and 1 trash."

(( RIGHT = COLUMNS, BOTTOM = LINES - 5, DX = RIGHT-20, DY = BOTTOM-3, SX = RIGHT-35, SY = BOTTOM-5, TX = RIGHT-60, TY = BOTTOM-6, DIR = 180 ))

cmd=$(
	enter 0
	enter 0
	enter 0
	set_delay 5
	move_vacuum ${RIGHT} ${BOTTOM} ${DIR}
	move_dust ${DX} ${DY}
	move_slime ${SX} ${SY}
	move_trash ${TX} ${TY}
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Return to Base"
details="Vacuum is manually sent to charging station."
expect="Vacuum is displayed in centre; Max dust, slime and trash; Vacuum is immediately told to return to base; When simulation starts, vacuum heads directly to charging station without collecting any rubbish."

cmd=$(
	enter 5
	enter 10
	enter 1000
	rtb
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Return to Base"
details="Vacuum battery falls below 25%."
expect="Vacuum is displayed in centre; Max dust, slime and trash; Vacuum starts normal operation with just 26% battery; When Battery level drops below 25%, Vacuum heads directly to charging station without collecting anymore rubbish."

cmd=$(
	enter 5
	enter 10
	enter 1000
	batt_lvl 25
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
category="Return to Base"
details="Vacuum load capacity exceeds 45g."
expect="Vacuum is displayed in centre; Max dust, slime and trash; Vacuum starts normal operation with 45g load; When load exceeds 45g, Vacuum heads directly to charging station without collecting anymore rubbish."

cmd=$(
	enter 5
	enter 10
	enter 1000
	load 45
	set_timeout 3
	pause_resume
)

run_test
#==============================================================================
