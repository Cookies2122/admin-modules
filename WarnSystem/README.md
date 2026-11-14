# WarnSystem

Предупреждения для игроков. Админ выдаёт их через меню, после лимита игрок получает бан сам. У каждого предупреждения есть срок, потом оно сгорает.

Автор: [ABKAM](https://github.com/ABKAM2023). Оригинал: [ABKAM2023/CS2-WarnSystem](https://github.com/ABKAM2023/CS2-WarnSystem). Перенос на новый SDK и Metamod 2.0: \_ded\_cookies.

## Что нужно

- [Metamod:Source](https://github.com/alliedmodders/metamod-source) 2.0 (KHook)
- [Admin System](https://github.com/Pisex/cs2-admin_system)
- [Utils](https://github.com/Pisex/cs2-menus)

## Команды

| Команда | Что делает |
| --- | --- |
| `!warn` | меню выдачи и снятия предупреждений (также `/warn`, в консоли `mm_warn`) |
| `!warn <steamid64>` | меню выдачи предупреждения игроку, который вышел |
| `!warn <steamid64> <причина> <время в секундах>` | сразу выдать предупреждение игроку, который вышел |
| `!warns` | свои активные предупреждения (также `/warns`, в консоли `mm_warns`) |

## admin_system.phrases.txt

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

## Конфиг

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

## Установка и сборка

Смотрите [README репозитория](../README.md): там описано, куда класть файлы и как собрать модуль.
