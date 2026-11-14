# Reserved_slots

Резервные слоты для Admin System. Игрок с нужным правом зайдёт даже на полный сервер.

Автор: [ABKAM](https://github.com/ABKAM2023). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [Admin System](https://github.com/Pisex/cs2-admin_system)
- [Utils](https://github.com/Pisex/cs2-menus)

Когда игроков без резерва больше, чем `public_slots`: новый игрок без резерва получает отказ, а если заходит игрок с резервом, с сервера отключается один игрок без резерва.

## Конфиг

`addons/configs/admin_system/reserved_slots.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `reserve_flag` | `@admin/reserve` | право или флаг Admin System, который даёт резерв |
| `public_slots` | `30` | сколько игроков без резерва может быть на сервере |
| `kick_reason_id` | `135` | причина отключения, 135 это "сервер заполнен" |

```
"ReservedSlots"
{
    "reserve_flag" "@admin/reserve" // Флаг для зарезервированных слотов
    "public_slots" "30" // Количество общедоступных слотов
    "kick_reason_id" "135" // NETWORK_DISCONNECT_REJECT_SERVERFULL
}
```

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
