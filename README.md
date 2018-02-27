# In development now as 31 jan 2018.

# SQL CUD Log

Tail the mysql log into this program and view all CUD (Create, update, delete) queries in different colours. The program ignores SELECT statements.

##
Removes noise from mysql log, and can filter queries to only show those that changes the database.

## Installation

* brew tap trondal/homebrew-repos
* brew install sqllogger

## Example

tail -f /var/log/mysql/query.log | sqllogger  
