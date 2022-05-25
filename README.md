# Projet-FAR-Client

Client side of the development of a messaging system with the C language

---
## Command Manual

| Command    | Parameters            | Actions                                                                                                                  | Access      |
|------------|-----------------------|--------------------------------------------------------------------------------------------------------------------------|-------------|
| /man       |                       | Displays the command manual                                                                                              | Everyone    |
| /pm        | pseudo                | Sends the message only to the user with pseudo "pseudo" as a private message                                             | Everyone    |
| /shutdown  |                       | Turn off the server                                                                                                      | Admins Only |
| /kick      | pseudo                | Kick the user with the pseudo "pseudo"                                                                                   | Admins Only |
| /luser-all |                       | List of all the user currently connected on the whole server                                                             | Admins Only |
| /quit      |                       | Allows you to quit the chat server                                                                                       | Everyone    |
| /admin     | password              | Give you all the permissions if the password is valid                                                                    | Everyone    |
| /luser     |                       | List of all the user currently connected on your channel                                                                 | Everyone    |
| /rename    | pseudo                | Change your username as "pseudo"                                                                                         | Everyone    |
| /sfile     |                       | Display a list of file. You can choose which one you want to send. Enter q for leave the selection menu                  | Everyone    |
| /lfile     |                       | List all the files stored on the server                                                                                  | Everyone    |
| /dfile     | filename              | Download the file "filename" from the server                                                                             | Everyone    |
| /cchannel  | name theme            | Create a new channel with the name (without space) in arguments                                                          | Admins Only |
| /rmchannel | number                | Remove the channel with the number in arguments                                                                          | Admins Only |
| /mchannel  | -n number name        | Modify the channel that correspond to the number in arguments with the name (without space) "name"                       | Admins Only |
|            | -t number theme       | Modify the channel that correspond to the number in arguments with the theme "theme"                                     | Admins Only |
|            | -nt number name theme | Modify the channel that correspond to the number in arguments with the name (without space) "name" and the theme "theme" | Admins Only |
| /lchannel  |                       | List all the channel of the server                                                                                       | Everyone    |
| /jchannel  | number                | Join the channel that correspond to the number                                                                           | Everyone    |

---

© Romain FREZIER & Etienne TILLIER - Polytech Montpellier