# Projet-FAR-Client

### What is the project ?

Client side of the development of a messaging system with the C language.

---

### To launch the program

` ./scriptClient.sh ip.of.the.server `

---

### Links

<a target="_blank" href="https://github.com/romainfrz/Projet-FAR-Server">
    <img alt="github link" src="https://img.shields.io/badge/github-server git-green?style=for-the-badge&logo=github">
</a>

<a target="_blank" href="https://github.com/romainfrz/Projet-FAR-Doc">
    <img alt="github link" src="https://img.shields.io/badge/github-doc git-blue?style=for-the-badge&logo=github">
</a>

---
### Command Manual

| Command    | Parameters            | Actions                                                                                                                  | Access      |
|------------|-----------------------|--------------------------------------------------------------------------------------------------------------------------|-------------|
| /man       |                       | Displays the command manual                                                                                              | Everyone    |
| /pm        | pseudo                | Sends the message only to the user with pseudo "pseudo" as a private message                                             | Everyone    |
| /shutdown  |                       | Turn off the server                                                                                                      | Admins Only |
| /kick      | pseudo                | Kick the user with the pseudo "pseudo"                                                                                   | Admins Only |
| /luser-all |                       | List of all the user currently connected on the whole server                                                             | Admins Only |
| /addword   | word                  | Add a word to censorship words list                                                                                      | Admins Only |
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
| /cform     | question number       | Create a new form with the question in arguments and with the number of answer expected                                  | Admins Only |
| /rmform    | number                | Remove the form with the number in arguments                                                                             | Admins Only |
| /lform     |                       | List all the form of the channel                                                                                         | Everyone    |
| /sform     | number                | See the result of the form with the number in arguments                                                                  | Everyone    |

---

© Romain FREZIER & Etienne TILLIER - Polytech Montpellier