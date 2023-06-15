# GuiScript
> A developer friendly library for creating debug UI in Godot 4 (The UI for the debug menu below is created with nothing but 28 lines of easy code).

![image](https://user-images.githubusercontent.com/38633608/233499345-9e38a930-936f-42c8-8c26-ab8d4022dbc2.png)  

You propably where there: You need a debug menu, maybe a few buttons, some number outputs in a simple layout. You start clicking it together in Godot, but it just takes far too much time for something you just need to do some testing and quick visualisations. GuiScript aims to solve this exact problem (but may also be used to prototype actual Game UI, even to build Game UI with the addition of some styling).

MIT License.

## Build
For now, there are no releases (I'll eventually come around to set up CI/CD to build it properly), but building this from scratch is not that hard.

This project makes heavy use of the example provided by the awesome people working on godot, so I'll link to the documentation: [GDExtension C++ Example](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html).

The specific steps you shall follow are:

0. Clone this repo AND it's submodules
0. "Building the C++ bindings" in the documentation linked above
0. (In the root dir of this repo) execute: `scons platform=<platform>` (add `target=template_release` if building for release; add `-jX`, but replacing X with the number of threads to use for building, e.g. -j6 for 6 threads). **Build for debug and release for all platforms you plan on using. See [here](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#toc-devel-compiling) for proper instructions on how to compile for each platform.**

After that, copy the 'bin'-folder (demo/bin) and guiscript.gdextension of the demo-project into your own project, and you are golden.

Open your project and check if you are able to see the class "GuiScript", deriving from Control in the "Add new node"-Screen.

## Usage
Layout GuiScript like a proper UI-Component. Any UI it will generate will live inside it. It's size will limit the UI's size.

Add a new script deriving from GuiScript and add it as script to your GuiScript-Node.

What you want to do exaclty now depends on your goals. Look at the examples below to see all available UI-Elements in action. Alternatively, take a look into the demo project.

In general you shall follow these rules three:

0. Whenever drawing a new frame, call begin_ui() first. This signals to guiscript, that a new frame has begun. Failing to do so will mean that new UI-Calls will add additional UI instead of updating it.
0. For each *_box() you open, you shall call end_box() once. This signals where the box shall be closed again and is essential for proper layouting. Imagine it as a closing tag in html.
0. Have fun and report bugs.


## Snippets

### Basic Introduction
![image](https://user-images.githubusercontent.com/38633608/233495675-065e264e-527a-492d-b0ec-7f15790a0f44.png)
```python
func _process(_delta):
	begin_ui()

    begin_hbox() # this creates a horizontal box

    vseparator() # vertical line separator
    label("Hello") # simple text label
    label("World!") # simple text label
    vseparator() # vertical line separator

    end_box() # this closes the horizontal box we previously opened

    hseparator() # horizontal line separator

    if button("Click Me!"):
        print("Button was clicked!")

```

### Table
> Procedural UI Generation ftw!

![image](https://user-images.githubusercontent.com/38633608/233495614-293b2f73-f426-42fa-9f7c-7ed171f2d94f.png)
```python
var table_data = [
	[13, 37, 32, 40],
	[50, 55, 56, 57],
	[34, 34, 54, 62],
	[42, 50, 13, 37],
	]

func _process(_delta):
	begin_ui()

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
```

### Cookie Clicker
![image](https://user-images.githubusercontent.com/38633608/233495737-19d0da13-19d2-4892-90a9-39005bcb5685.png)
```python
var clicks = 0.0
var upgrade_cost = 5
var passive = 0.0

func _process(delta_time):
	begin_ui()

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
```

# Contribution
In general, contributions are welcome. As this project is maintained by a pretty busy student, expect some time to pass from PR to feedback. This project is intended to be simple and minimalistic, so only start working on something if you see most people using this also using your contribution.

Feel free to develop own flavours of this, or to use this as a base for something bigger. As long as you honor the license, I'll honor your project :D

# Inner Workings, Performance
GuiScript is based on a virtual DOM. The elements of the virtual DOM manage their counterpart in the real Godot UI and encapsulate it's capabilities. If they are invalidated, they will remove the real UI-Node from the tree in godot.

By using this system, the UI will only be rebuilt if a disruptive update is sent (one, that suddenly requires a completly different node at the same position, invalidating the old one), and will only rebuild the parts that are actually required to be rebuilt. If an update can be represented by simply updating an existing component, exactly that will be done. This makes GuiScript reasonably performant (but obviously not quite as performant as creating your own custom dev-menus).

# Testing, Bugs and Further Developement
GuiScript is an almost 1:1-Port of an Godot3 Engine Module with proper code coverage. The tests are yet to be ported. For testing this port, mostly practical testing was done. GuiScript is used in some game projects of mine to build quite big debug-ui-stuff, so I always got incentive to fix bugs and extend this project.
