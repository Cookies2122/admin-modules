<h1 align=center><code>Admin Modules</code></h1>

<div align=center>
  <img src=https://img.shields.io/badge/Counter--Strike%202-Metamod%202.0%20(KHook)-orange?style=flat-square alt=metamod>
  <a href=https://github.com/Cookies2122/admin-modules/commits><img src=https://img.shields.io/github/last-commit/Cookies2122/admin-modules?style=flat-square alt="last commit"></a>
  <a href=LICENSE><img src=https://img.shields.io/github/license/Cookies2122/admin-modules?style=flat-square alt=license></a>
</div>
<br>

Модули для [Admin System](https://github.com/Pisex/cs2-admin_system) на Counter-Strike 2. Здесь мой модуль и модули ABKAM, перенесённые на новый SDK и Metamod 2.0. Все модули работают на Metamod 2.0 (KHook).

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [Admin System](https://github.com/Pisex/cs2-admin_system)
- [Utils](https://github.com/Pisex/cs2-menus)

## Установка

1. Соберите модуль (раздел [Сборка](#сборка)).
2. Скопируйте содержимое `build/package` в папку `csgo` на сервере.
3. Проверьте конфиг модуля в `addons/configs/admin_system/`.
4. Если у модуля есть фразы, допишите их в `addons/translations/admin_system.phrases.txt`.
5. Перезапустите сервер или смените карту.

## Список модулей

| Модуль | Что делает | Автор |
| --- | --- | --- |
| [[AS] Anti Sliv](#as-anti-sliv) | Защита от слива админки. Если админ за короткое время выдаёт слишком много банов или мутов, его самого банят навсегда. Причина пишется в чат и в лог `antisliv.log`. | [\_ded\_cookies](https://github.com/Cookies2122) |
| [Reserved_slots](#reserved_slots) | Резервные слоты для Admin System. Игрок с нужным правом зайдёт даже на полный сервер. | [ABKAM](https://github.com/ABKAM2023) |
| [WarnSystem](#warnsystem) | Предупреждения для игроков. Админ выдаёт их через меню, после лимита игрок получает бан сам. У каждого предупреждения есть срок, потом оно сгорает. | [ABKAM](https://github.com/ABKAM2023) |

## Модули

### [AS] Anti Sliv

Защита от слива админки. Если админ за короткое время выдаёт слишком много банов или мутов, его самого банят навсегда. Причина пишется в чат и в лог `antisliv.log`.

**Конфиг**

`addons/configs/admin_system/antisliv.ini` (при сборке в пакет не попадает, скопируйте файл `configs/admin_system/antisliv.ini` туда сами)

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `round_refresh` | `2` | раз в сколько раундов обнулять счётчики банов и мутов админа |
| `max_mutes` | `5` | сколько мутов за этот промежуток считается сливом |
| `max_bans` | `3` | сколько банов за этот промежуток считается сливом |
| `flags_immunity` | `z` | флаги админов, которых модуль не проверяет, можно несколько подряд |

```
"AntiSliv"
{
    // Меняя эти настройки вы можете уменьшать и увеличивать "жёсткость" работы плагина.
    
    // Каждые N раундов будет очищаться информация о банах и мутах администратора
    "round_refresh"     "2"
    
    // Сколько мутов должен сделать администратор за N раундов (round_refresh), 
    // чтобы получить бан за подозрение на слив
    "max_mutes"         "5"
    
    // Сколько банов должен сделать администратор за N раундов (round_refresh), 
    // чтобы получить бан за подозрение на слив
    "max_bans"          "3"
    
    // Флаги которые имеют иммунитет от проверок плагина
    // Можно писать несколько флагов подряд, если хоть один найдётся
    // у администратора то он получит иммунитет от проверок
    "flags_immunity"    "z"
}
```

### Reserved_slots

Резервные слоты для Admin System. Игрок с нужным правом зайдёт даже на полный сервер.

Когда игроков без резерва больше, чем `public_slots`: новый игрок без резерва получает отказ, а если заходит игрок с резервом, с сервера отключается один игрок без резерва.

**Конфиг**

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

### WarnSystem

Предупреждения для игроков. Админ выдаёт их через меню, после лимита игрок получает бан сам. У каждого предупреждения есть срок, потом оно сгорает.

**Команды**

| Команда | Что делает |
| --- | --- |
| `!warn` | меню выдачи и снятия предупреждений (также `/warn`, в консоли `mm_warn`) |
| `!warn <steamid64>` | меню выдачи предупреждения игроку, который вышел |
| `!warn <steamid64> <причина> <время в секундах>` | сразу выдать предупреждение игроку, который вышел |
| `!warns` | свои активные предупреждения (также `/warns`, в консоли `mm_warns`) |

**admin_system.phrases.txt**

Допишите внутрь блока `"Phrases"`:

<details>
<summary>Фразы (34)</summary>

```
"Chat_Prefix"
{
	"ru"		"{RED}[WarnSystem] {DEFAULT}"
	"ua"		"{RED}[WarnSystem] {DEFAULT}"
	"en"		"{RED}[WarnSystem] {DEFAULT}"
}
"Chat_WarnReceived"
{
	"ru"		"Вы получили предупреждение (%i/%i): %s. Подробнее: !warns"
	"ua"		"Ви отримали попередження (%i/%i): %s. Детальніше: !warns"
	"en"		"You received a warning (%i/%i): %s. Details: !warns"
}
"Chat_WarnIssued"
{
	"ru"		"Вы выдали предупреждение игроку %s (%i/%i)"
	"ua"		"Ви видали попередження гравцю %s (%i/%i)"
	"en"		"You issued a warning to %s (%i/%i)"
}
"Chat_WarnIssuedOffline"
{
	"ru"		"Вы выдали предупреждение оффлайн игроку %s (%i/%i)"
	"ua"		"Ви видали попередження офлайн гравцю %s (%i/%i)"
	"en"		"You issued a warning to offline player %s (%i/%i)"
}
"Chat_WarnBan"
{
	"ru"		"%s забанен за превышение лимита предупреждений"
	"ua"		"%s забанений за перевищення ліміту попереджень"
	"en"		"%s was banned for reaching the warning limit"
}
"Chat_NoWarnings"
{
	"ru"		"Для этого игрока нет предупреждений"
	"ua"		"Для цього гравця немає попереджень"
	"en"		"No warnings to remove for this player"
}
"Chat_WarnRemovedTarget"
{
	"ru"		"Одно предупреждение снято. Текущее количество: %i. Подробнее: !warns"
	"ua"		"Одне попередження знято. Поточна кількість: %i. Детальніше: !warns"
	"en"		"One warning was removed. Current: %i. Details: !warns"
}
"Chat_WarnRemovedAdmin"
{
	"ru"		"Снято одно предупреждение с игрока %s"
	"ua"		"Знято одне попередження з гравця %s"
	"en"		"Removed one warning from %s"
}
"Chat_SelfWarnNotAllowed"
{
	"ru"		"Вы не можете выдать предупреждение самому себе"
	"ua"		"Ви не можете видати попередження самому собі"
	"en"		"You cannot warn yourself"
}
"Chat_ImmunityBlocked"
{
	"ru"		"Цель имеет иммунитет - предупреждение не выдано"
	"ua"		"Ціль має імунітет - попередження не видано"
	"en"		"Target has immunity - warning not issued"
}
"Chat_WarnDuplicateBlocked"
{
	"ru"		"У игрока уже есть активное предупреждение за эту причину"
	"ua"		"У гравця вже є активне попередження за цю причину"
	"en"		"Player already has an active warning for this reason"
}
"Unit_Day"
{
	"ru"		"дн"
	"ua"		"дн"
	"en"		"d"
}
"Unit_Hour"
{
	"ru"		"ч"
	"ua"		"год"
	"en"		"h"
}
"Unit_Min"
{
	"ru"		"мин"
	"ua"		"хв"
	"en"		"m"
}
"Unit_Sec"
{
	"ru"		"сек"
	"ua"		"с"
	"en"		"s"
}
"Menu_ItemWarnSystem"
{
	"ru"		"Система предупреждений"
	"ua"		"Система попереджень"
	"en"		"Warn System"
}
"Menu_SelectReason"
{
	"ru"		"Выберите причину предупреждения"
	"ua"		"Оберіть причину попередження"
	"en"		"Select warning reason"
}
"Menu_WarningsFor"
{
	"ru"		"Предупреждения для %s (%i/%i)"
	"ua"		"Попередження для %s (%i/%i)"
	"en"		"Warnings for %s (%i/%i)"
}
"Menu_IssueWarning"
{
	"ru"		"Выдать предупреждение"
	"ua"		"Видати попередження"
	"en"		"Issue warning"
}
"Menu_RemoveWarning"
{
	"ru"		"Снять последнее предупреждение"
	"ua"		"Зняти останнє попередження"
	"en"		"Remove last warning"
}
"Menu_SelectPlayer"
{
	"ru"		"Выберите игрока"
	"ua"		"Оберіть гравця"
	"en"		"Select player"
}
"Menu_OfflineWarnings"
{
	"ru"		"Оффлайн предупреждения"
	"ua"		"Офлайн попередження"
	"en"		"Offline warnings"
}
"Menu_SelectOfflinePlayer"
{
	"ru"		"Выберите оффлайн игрока"
	"ua"		"Оберіть офлайн гравця"
	"en"		"Select offline player"
}
"Menu_RemoveSelect"
{
	"ru"		"Выберите предупреждение для снятия"
	"ua"		"Виберіть попередження для зняття"
	"en"		"Select warning to remove"
}
"Menu_NoPlayers"
{
	"ru"		"Нет доступных игроков"
	"ua"		"Немає доступних гравців"
	"en"		"No players available"
}
"Menu_NoOfflinePlayers"
{
	"ru"		"Нет недавно вышедших игроков"
	"ua"		"Немає нещодавно вийшовших гравців"
	"en"		"No recently disconnected players"
}
"Menu_MyWarnings"
{
	"ru"		"Ваши предупреждения (%i)"
	"ua"		"Ваші попередження (%i)"
	"en"		"Your warnings (%i)"
}
"Menu_WarnExpires"
{
	"ru"		"Истекает: %s"
	"ua"		"Спливає: %s"
	"en"		"Expires: %s"
}
"Menu_WarnExpireNever"
{
	"ru"		"Не истекает"
	"ua"		"Не спливає"
	"en"		"Does not expire"
}
"Menu_ConfirmReason"
{
	"ru"		"Подтвердите предупреждение"
	"ua"		"Підтвердіть попередження"
	"en"		"Confirm warning"
}
"Menu_WarnDetail"
{
	"ru"		"Предупреждение #%i"
	"ua"		"Попередження #%i"
	"en"		"Warning #%i"
}
"Menu_NoWarningsSelf"
{
	"ru"		"У вас нет предупреждений"
	"ua"		"У вас немає попереджень"
	"en"		"You have no warnings"
}
"Menu_WarnDuplicate"
{
	"ru"		"Уже есть предупреждение за эту причину. Истекает через: %s"
	"ua"		"Вже є попередження з цієї причини. Спливає через: %s"
	"en"		"There is already a warning for this reason. Expires in: %s"
}
"Menu_WarnDuplicateBlocked"
{
	"ru"		"Повторная выдача запрещена"
	"ua"		"Повторна видача заборонена"
	"en"		"Duplicate warn is disabled"
}
```

</details>

**Конфиг**

`addons/configs/admin_system/warnsystem.ini`

| Ключ | По умолчанию | Что делает |
| --- | --- | --- |
| `max_warnings` | `3` | сколько предупреждений до бана |
| `ban_duration` | `1440` | длительность бана в секундах, 0 навсегда |
| `ban_reason` | `Достигнут лимит предупреждений` | причина бана |
| `server_id` | `-1` | -1 взять punish_server_id из core.ini, иначе свой id сервера |
| `command` | `!warn\|/warn` | чат-команды для админов через `\|` |
| `console_command` | `mm_warn` | консольные команды для админов через `\|` |
| `player_command` | `!warns\|/warns` | чат-команды для игроков через `\|` |
| `player_console_command` | `mm_warns` | консольные команды для игроков через `\|` |
| `flag` | `@admin/warn` | право Admin System для меню предупреждений |
| `allow_duplicate_reason` | `0` | 1 можно выдать ещё одно предупреждение за ту же причину, 0 нельзя, пока старое активно |
| `offline_recent_limit` | `10` | сколько последних вышедших игроков показывать в списке |
| `warn_sound` | `sounds/buttons/blip2.vsnd` | звук при выдаче, пусто чтобы выключить |
| `notify_channels` | `chat\|center` | куда писать уведомления: `chat`, `center` или `chat\|center` |
| `category` | `punishments` | категория в меню админки: `players`, `punishments` или своё имя |

В секции `reasons` лежат причины: `text` текст причины, `expire_seconds` через сколько секунд предупреждение сгорит.

<details>
<summary>Весь файл warnsystem.ini</summary>

```
"warnsystem"
{
    "max_warnings"      "3"              // максимум предупреждений до авто-бана
    "ban_duration"       "1440"          // длительность бана в секундах; 0 = навсегда
    "ban_reason"        "Достигнут лимит предупреждений" // причина бана
    "server_id"         "-1"             // -1 = брать punish_server_id из core.ini, иначе указать своё

    "command"           "!warn|/warn"    // чат-команды через |
    "console_command"   "mm_warn"        // консольная/серверная команда (можно несколько через |)
    "player_command"    "!warns|/warns"  // команда для игроков: показать свои предупреждения
    "player_console_command" "mm_warns"  // консольная/серверная команда для просмотра своих предупреждений (несколько через |)
    "flag"              "@admin/warn"    // флаг/разрешение для доступа к меню предупреждений

    "allow_duplicate_reason" "0"          // 1 = можно выдать пред с той же причиной, 0 = запретить повтор за активную причину

    "offline_recent_limit" "10"          // сколько последних вышедших игроков показывать в оффлайн-списке

    "warn_sound"        "sounds/buttons/blip2.vsnd"  // путь к звуку (play %s); оставить пустым чтобы отключить

    "notify_channels"   "chat|center"    // chat, center или chat|center - куда слать уведомления о выдаче/снятии/бане

    // category: players или punishments = штатные категории; любое другое имя => будет создана/использована своя категория с таким названием
    "category"          "punishments"

    "reasons"
    {
        "1"
        {
            "text" "Флуд / спам" // текст причины
            "expire_seconds" "604800" // время истечения причины в секундах
        }
        "2"
        {
            "text" "Токсичное поведение"
            "expire_seconds" "259200"
        }
        "3"
        {
            "text" "Гриферство"
            "expire_seconds" "86400"
        }
    }
}
```

</details>

## Что поменялось в модулях ABKAM

- Переведено на новый SDK ([Wend4r/sourcesdk](https://github.com/Wend4r/sourcesdk)), старый после обновления CS2 от 12.11.2026 уже не подходит.
- Работает только на Metamod 2.0 (KHook), старый Metamod на SourceHook больше не поддерживается.
- Заголовки Utils обновлены под текущую версию, имена интерфейсов теперь `UTILS_INTERFACE` и `MENUS_INTERFACE`.
- Своя функция `GameEntitySystem()` убрана, в новом SDK entity system берётся через `IGameResourceService`.
- SchemaEntity обновлена: актуальные оффсеты виртуальных функций.
- WarnSystem: `ban_duration` со значением -1 давал бан, который сразу истекал. Теперь -1 и 0 означают бан навсегда.

## Сборка

Собирается на Linux. Нужны clang, python3, cmake и [AMBuild](https://github.com/alliedmodders/ambuild). Все команды ниже выполняются из одной папки.

**1. SDK.** Нужен [sourcesdk](https://github.com/Wend4r/sourcesdk) не старее обновления CS2 от 12.11.2026. Собирается один раз:

```bash
git clone --recursive https://github.com/Wend4r/sourcesdk hl2sdk-cs2
cmake -S hl2sdk-cs2 -B hl2sdk-cs2/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DSOURCESDK_AM_DEFINES=ON -DSOURCESDK_USE_MINIMAL_PROTOS=OFF
cmake --build hl2sdk-cs2/build -j$(nproc)
export HL2SDKCS2=$PWD/hl2sdk-cs2
```

**2. Metamod.** Нужен Metamod 2.0 с KHook, ветка `master`. Со старым Metamod на SourceHook сборка остановится с ошибкой.

```bash
git clone --recursive https://github.com/alliedmodders/metamod-source
```

**3. Модуль.** Папка SchemaEntity уже лежит в корне репозитория, модули берут её оттуда.

```bash
git clone https://github.com/Cookies2122/admin-modules
cd admin-modules/WarnSystem
mkdir build && cd build
python3 ../configure.py --enable-optimize --sdks=cs2 --targets=x86_64 --mms_path=$PWD/../../../metamod-source --hl2sdk-manifests=../hl2sdk-manifests
ambuild
```

Готовые файлы появятся в `build/package`. Для другого модуля поменяйте папку во второй строке.

## Авторы

| Модуль | Автор | Оригинал |
| --- | --- | --- |
| [[AS] Anti Sliv](%5BAS%5D%20Anti%20Sliv) | [\_ded\_cookies](https://github.com/Cookies2122) | этот репозиторий |
| [Reserved_slots](Reserved_slots) | [ABKAM](https://github.com/ABKAM2023) | [ABKAM](https://github.com/ABKAM2023) |
| [WarnSystem](WarnSystem) | [ABKAM](https://github.com/ABKAM2023) | [ABKAM2023/CS2-WarnSystem](https://github.com/ABKAM2023/CS2-WarnSystem) |

Перенос модулей ABKAM на новый SDK и Metamod 2.0 и исправления: \_ded\_cookies.

## Лицензия

Репозиторий распространяется по лицензии GPL-3.0, текст в файле [LICENSE](LICENSE). Авторские права на модули остаются за их авторами из таблицы выше.
