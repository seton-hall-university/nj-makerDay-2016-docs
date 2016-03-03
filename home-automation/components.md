<!---
title: Components
summary: This document describes basic components.
author: G. L. Clark, II
date Created: March 2, 2016
date Modified:{{ file.mtime }}
filename: circuitry-basics.md
--->

# Components[^1]

To build circuits, you will need to become familiar with a few basic components. These components may seem simple, but are the bread and butter of most electronics projects.

## Resistors[^2]

As the name implies, resistors add resistance to the circuit and reduces the flow of electrical current. In a circuit diagram they are represented as a pointy squiggle with a value next to it.

<figure style="margin: 15px 0; width: 100%; border:1px solid lightgray; text-align:center">
<img src="../assets/images/resistors-schematic.svg" alt="Resistor Schematic Display" width="250px">
<figcaption style="ackground-color: aliceblue; border-top: 1px solid lightgray; font-style: italic;">Resistor Schematic Display</figcaption>
</figure>

The different markings on the resistor represent the value of resistance provided.

Resistors also come with different wattage ratings. For most low-voltage DC circuits, 1/4 watt resistors should be suitable.

You read the values from left to right towards the (typically) gold band. The first two colors represent the resistor value. The third represents the multiplier. And the fourth (the gold band) represents the tolerance or precision of the component. You can tell the value of each color by looking at a resistor color value chart.

<figure style="margin: 15px 0; width: 100%; border:1px solid lightgray; text-align:center">
<img src="../assets/images/resistors.svg" alt="Resistor Schematic Display" width="500px">
<figcaption style="ackground-color: aliceblue; border-top: 1px solid lightgray; font-style: italic;">Various Resistors</figcaption>
</figure>

Or... to make your life easier, you could look up the values using a graphical resistance calculator.

For example, a resistor with the markings brown, black, orange, gold will translate as follows:

1 (brown) 0 (black) x 1,000 = 10,000 with a tolerance of +/- 5%

Any resistor of over 1000 ohms is typically shorted using the letter K; e.g.:
- 1,000 ohms = 1K
- 3,900 ohms = 3.9K
- 470,000 ohms = 470K.

Values of ohms over a million are represented using the letter M. In this case, 1,000,000 ohms would become 1M.

----
[^1]: http://www.instructables.com/id/Basic-Electronics/step5/Basic-Components/
[^2]: http://www.instructables.com/id/Basic-Electronics/step6/Resistors/
