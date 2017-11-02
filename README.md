## Kaleidoscope-PrefixLayer

Based on [a cool trick from ilianaw][original], this plugin allows to to make all keys on a layer act as if they're prefixed by some keystroke.
The original use-case is for using Tmux or Screen - for example, you can have a layer of keys wherein all the keys in the layer act as if you've hit Control-B before the key.

## Using the plugin

Add the plugin to your available libraries by cloning it into your `Arduino-Boards/libraries` directory.

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-PrefixLayer.h>

// Have an enum for layers
// or some other way of assigning numbers to layers
enum {
  _BASE,
  _TMUX,
};

static const kaleidoscope::PrefixLayer::dict_t prefixlayerdict[] PROGMEM =
    PREFIX_DICT({_TMUX, PREFIX_SEQ(LCTRL(Key_B))});

void setup(void) {
  Kaleidoscope.setup();
  Kaleidoscope.use(&PrefixLayer);

  PrefixLayer.dict = prefixlayerdict;
}
```

## Plugin methods

The plugin provides the `PrefixLayer` object, with the following property.

### `.dict`

> Set the map of layers and prefix keys. This should be specified with the PREFIX_DICT() macro.
> The arguments to the macro should be a series of pairs like `{layer_number, prefix_sequence}`.
> The `prefix_sequence` section should be constructed with the
> `PREFIX_SEQ` macro, and should be a series of keys that will be tapped before the key in the layer.
>
> The dict must be stored in `PROGMEM` as shown above.

## Further reading

Starting from the [example][] is the recommended way of getting started with the plugin.

  [original]: https://github.com/ilianaw/Model01-Firmware/commit/7dad53bf1855e68a4c93a1686cad5e75b539cb0b
  [example]: https://github.com/jamesnvc/Kaleidoscope-PrefixLayer/blob/master/examples/PrefixLayer/PrefixLayer.ino
