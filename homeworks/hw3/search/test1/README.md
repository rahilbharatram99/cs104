# Test Case 1
Check correct error message for filename that does not exist pageA.md

Page1: $(COLORS)
	Key Words: blue yellow green red black white
	OutGoingLinks: page1.md page2.txt page3.md
	Incoming: page3.md

Page2: $(NUMBERS)
	Key Words: 11 12 1 2 3 4 6 
	OutgoingLinks:
	Incoming: page1.md page3.md
	
Page3: $(COLORS) $(NUMBERS)
	Key Words: 11 12 1 blue yellow green 
	OutgoingLinks: page1.md page2.txt
	Incoming: page1.md