# hotkey_manager_linux

[![pub version][pub-image]][pub-url]

[pub-image]: https://img.shields.io/pub/v/hotkey_manager_linux.svg
[pub-url]: https://pub.dev/packages/hotkey_manager_linux

The Linux implementation of [hotkey_manager](https://pub.dev/packages/hotkey_manager).

## Backends

On X11, global shortcuts are registered with
[`keybinder-3.0`](https://github.com/kupferlauncher/keybinder).

On Wayland, global shortcuts are registered with the
[`org.freedesktop.portal.GlobalShortcuts`](https://flatpak.github.io/xdg-desktop-portal/docs/doc-org.freedesktop.portal.GlobalShortcuts.html)
desktop portal. The compositor may show a permission dialog the first time
shortcuts are bound. The portal backend emits both `onKeyDown` and `onKeyUp`
events when the compositor sends activation and deactivation signals.

The Wayland portal does not have portable equivalents for the `capsLock` and
`fn` modifiers, so those modifiers may be ignored by the compositor.

## License

[MIT](./LICENSE)
