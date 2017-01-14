# SetBrightness
Replacement for xbacklight (broken on my computer with bumblebee)

#Usage :

setbrightness [OPTION] {VALUE}
	OPTIONS :
		--get : curent/max brightness
		--set VALUE : set the brightness to VALUE 
		--inc VALUE or + VALUE : add VALUE to the current brightness
		--dec VALUE or - VALUE : sub VALUE to the current brightness


#TODO :
	
	- add config file 
		min_value (right now set to 10)
		path to the different files (right now hardcoded in the .c file
	- edit readme to include examples of i3 / openbox configs files using SetBrightness
	- sleeping ... 
