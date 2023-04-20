extends GuiScript


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# small helper
var delta_time = 0

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	delta_time = delta
	
	begin_ui()
	
	# activate whatever sample you want to see.
	# or activate all to see all.
	drawWithTitle("Basics","drawBasics")
	drawWithTitle("Draw Table", "drawTable")
	drawWithTitle("Cookie Clicker", "drawCookieClicker")


# a simple helper to make any combination of function-components look good.
func drawWithTitle(title, callName):
	hseparator()
	label("Sample: " + title)
	begin_hbox() # embeds the sample in an additional hbox to make it not grow to maximum size (purely visual effect)
	
	call(callName)
	
	begin_vbox() # fills empty space left over.
	end_box()
	
	end_box()
	

func drawBasics():
	begin_hbox() # this creates a horizontal box

	vseparator() # vertical line separator
	label("Hello") # simple text label
	label("World!") # simple text label
	vseparator() # vertical line separator

	end_box() # this closes the horizontal box we previously opened

	hseparator() # horizontal line separator

	if button("Click Me!"):
		print("Button was clicked!")

var table_data = [
	[13, 37, 32, 40],
	[50, 55, 56, 57],
	[34, 34, 54, 62],
	[42, 50, 13, 37],
	]
func drawTable():
	begin_vbox()
	
	for row in table_data:
		hseparator()
		begin_hbox()
		
		for e in row:
			vseparator()
			label(str(e))
			
		vseparator()
		end_box()
		
	hseparator()
	end_box()
	
var clicks = 0.0
var upgrade_cost = 5
var passive = 0.0

func drawCookieClicker():
	clicks += passive * delta_time
	
	begin_hbox()
	
	begin_vbox()
	label("clicks: " + str(floor(clicks)))
	label("passive: " + str(passive))
	
	if button("Click Me!"):
		clicks += 1
	
	end_box()
	
	vseparator()
	var upgrade_cost_string = str(ceil(upgrade_cost))
	var upgrade_possible = clicks >= upgrade_cost

	if button("Buy Upgrade(" + upgrade_cost_string + ")") && upgrade_possible:
		passive += 0.5
		clicks -= upgrade_cost
		upgrade_cost *= 1.5
		
	end_box()
	end_box()
	hseparator()
