# Capacitors[^1]

A capacitor is a component that stores electricity. When there's a drop in electricity, it will discharge some of the storage to maintain a steady current. Think of it as a water storage tank that releases water when there is a drought to ensure a steady stream.

Capacitors are measured in [farads](https://en.wikipedia.org/wiki/Farad). The values typically encountered in picofarad (pF), nanofarad (nF), and microfarad (uF). These are often used interchangeably and it helps to have a conversion chart at hand.

The most commonly encountered types of capacitors are ceramic disc capacitors and electrolytic capacitors. Ceramic disc capacitors look like M&Ms with two wires sticking out of them. Electrolytic capacitors look like small cylindrical tubes with two wires coming out the bottom. Sometimes, these types of capacitors will have the wires on each end instead.

<figure>
<img src="../assets/images/capacitors.svg" alt="Various Capacitos">
<figcaption>Various Capacitors</figcaption>
</figure>

Ceramic disc capacitors are non-polarized. Meaning that electricity can pass through them no matter how they are placed in the circuit. They are typically marked with a number code which needs to be decoded. Insights on reading ceramic capacitors can be [found here](http://electronics.stackexchange.com/a/16637) and [here](http://electronics.stackexchange.com/questions/18102/ceramic-capacitors-how-to-read-2-digit-markings). This type of capacitor is typically represented in a schematic as two parallel lines.

Electrolytic capacitors are typically polarized. This means that one leg needs to be connected to the ground side of the circuit and the other leg must be connected to power. If it is connected backwards, it won't work. Electrolytic capacitors have the value written on them, typically represented in uF. They also mark the leg which connects to ground with a minus symbol (-). This capacitor is represented in a schematic as a side-by-side straight and curved line. The straight line represents the end which connects to power and the curve connected to ground.

<figure>
<img src="../assets/images/capacitors-schematic.svg" alt="Various capacitors schematic">
<figcaption>Various capacitors as seen on a schematic</figcaption>
</figure>

---
#### References

[^1]: http://www.instructables.com/id/Basic-Electronics/step7/Capacitors
