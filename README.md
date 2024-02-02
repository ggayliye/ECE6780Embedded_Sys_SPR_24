# ECE6780Embedded_Sys_SPR_24
Lab Repo for class ECE 6780  - Embedded System Design - Spring 2024, The University of Utah.

Authors : William Carr and Kyle G. Gayliyev <br>
Team Name: cs3500survivors<br>
Date: 17-April-2023<br>
Course: CS 3500, University of Utah, School of Computing<br>
GitHub IDs: ggayliye and willcarr198<br>
Repo: https://github.com/uofu-cs3500-spring23/assignment-nine---web-server---sql-cs3500survivors <br>
Date: 26-April-2023 Time (of when submission is ready to be evaluated)<br>
Solution: SQL and Web Server<br>
Copyright: CS 3500, Kyle G. Gayliyev and William Carr - This work may not be copied for use in
Academic Coursework.

<u>**ASSIGNMENT 9:**</u><br>

## Overview of the SQL and Web Server Solution functionality

The purpose of the "SQL and Web Server" Solution is to build a Web Server that 
can store and retrieve information from a database and publish it on a web browser.
The web pages will be built based on the data received from the database along with a
simply designed webpage. 

This project can be described in two parts: Storying data into the database, and
pulling data from the database and publishing it on a web browser locally (localhost).

To store data, a database tool will be connected to our project in the server. Publishing 
info in a web browser will be scripted in HTML. We used Cascading Style Sheets (CSS) [8] 
to design our web pages, and  JaveScript to manipulate some HTML elements. 
More detailed information is given in the next sections below.

A networking/communication project is also needed to successfully operate (send and receive 
messages, commands, etc.) on the web page locally.

### DataBase 

**Introduction About The Database Project**<br>
We use SQL Server Management Studio (SSMS) as a database tool. The SSMS is an integrated 
environment for managing any SQL infrastructure, from SQL Server to Azure SQL 
Database. SSMS provides tools to configure, monitor, and administer instances of 
SQL Server and databases [7].

A total of six tables were created in the database. Creating a database may come with some rules,
such as ensuring data integrity. For example, building relationships between tables, assigning
primary and foreign keys, enforcing auto-generated fields, and not allowing altering
or entering data without entering some other data. However, for the sake of easiness,
in this project, we did not enforce many database rules strictly. This will also make the 
testing easier as someone who may not be well informed about our data structure 
may easily manipulate our tables in the database. In real-world applications,
this practice should be avoided.

All data fields are non-nullable. This means that when new data are entered, 
all columns should be filled otherwise entering the command may fail.

Created tables in our database with column names and data types are listed below. <br>

<ins>"Players" Table</ins> : "PlayerID" (int)[primary], "PlayerName" (varchar(50)),"PlayerScore" (int)<br>
<ins>"Games" Table</ins> : "PlayerName(varchar(50)), "HighMass"(int), GameID"(int), "WinnerPlayerID"(int), 
"StartTime"(datetime), "EndTime"(datetime), TimeSizeReached850X850InMiliiSec(varchar(50)) <br>
<ins>"GameState" Table</ins> : "GameID"(int)[primary], "PlayersEaten"(int), "ActivePlayersNum"(int), "MaxSplit"(int)<br>
<ins>"Clans" Table</ins> : "ClanID"(int)[primary], "ClanName" (varchar(50))<br>
<ins>"ClanMembers" Table</ins> : "ClanID"(int), "PlayerID"(int)<br>
<ins>"RecordsSinglePlayer" Table</ins> : "GameID"(int), "WonOrLost"(varchar(50))<br>

+ <em>[primary]</em> means the primary key in the table.
+ <em>(int)</em> indicates an integer datatype.
+ <em>(varchar(50))</em> indicates a string datatype that can hold up to 50 characters.
+ <em>(datetime)</em> date and time datatype. It will store the date and time.<br>

Table Relationships:<br>
There is the one-and-one relationship between our tables. They are outlined below:<br>
- Clans -> ClanMembers
- Players -> ClanMembers
- Games -> GameState 
- Players -> Games
- Players -> RecordsSinglePlayer
- Games -> RecordsSinglePlayer

<em>Note: These relationships are not enforced in our database as of today. We decided to remove for sake of easy testing the database and keep it simple.</em> 

### Web Server Project:

Web Server Project is a Console App. The coding language is C#. The Framework is ".NET 7.0".

It includes code to establish a connection with the database and local server. 
It will also serve as a communication "handler", where data will be sent and 
received between the database and the local host/web browser.

Webserver Project also help to save data from our previous project, AGARIO game. It stores player's name,
high mass, game id, winnerplayerID, start and end time of the game, and duration of the game when the player reaches a specific mass.

### HTML

Web server pages are created in HTML files. Therefore, their extensions are in ".html".
Starting/landing page is "index.html".
HTML files are located in the "html" folder. The html folder also contains two other subfolders
named "css" and "js". The "css" folder includes the styling cascade file named "style.css" and the "js"
folder includes a JavaScript file named "script.js".

The CSS file includes over 20 styling code. The js file includes 2-3 JavaScript functions for the HTML.

The JavaScript file also includes a server connection code as an alternative to the server code we have in our 
Webserver project. To run the JavaScript server, first, open your command window and 
make your directory the place where the "script.js" is located. Then, type "
Node script.js" to the command. It should start on the local server. You may need to
download Node.js and its packages after that. If you don't have Node.js
downloaded and if you would like to download, you will follow these steps to be able
to run the javascript file: type 1) npm install express --save into the command line.
Once done secondly, type 2) npm install mssql --save on the command line. Now it should be ready to
start the local server by typing "Node script.js". Then, come to your browser and type "http://localhost:11001/".
Our "index" page should load. Other pages are not linked in this JavaScript program.

To see our HTML pages that are styled with CSS, find the "index.html". Click to open in a browser. You should see
a designed page. You should also be able to move in between pages.

### Communications Project 
Communications is a Class Library type file in MS Visual Studio. This file will be
used by other programs to achieve their goals.

Communications Project Class contains an abstract for a networking object and its
various async methods( such as ReadAsync, WriteAsync, AcceptTcpClientAsync).

This project defines "public class Networking" and uses the namespace "Communications".
The class will interact with programs that want networking (such as Client and Server GUIs?)
using a callback mechanism. The interacting programs provide a delegate through a function
(such as HandleMessage) that the networking object will call when a full message comes from
the network.

The Networking code will use the following delegates. They will be stored by the networking 
object constructor and called inside the networking code by named (given name) event.<br>
- void ReportMessageArrived( Networking channel, string message );
- void ReportDisconnect( Networking channel );
- void ReportConnectionEstablished( Networking channel );

This project supports the following API:<br>
- public string ID (property) 
- public Networking( ILogger logger, ReportConnectionEstablished onConnect, ReportDisconnect 
  onDisconnect, ReportMessageArrived onMessage, char terminationCharacter);
- public void Connect(string host, int port)
- public async void AwaitMessagesAsync( bool infinite=true )
- public async void WaitForClients( int port, bool infinite 
- public void StopWaitingForClients()
- public void Disconnect()
- public async void Send( string text)

Note. In this project, we used the instructor's communication project file named "communications.dll"
It's stored in the "lib" folder.

<pre><ins>Future extensions</ins> :  There will be no future additions to this project. </pre>

# Partnership

<ins> Progress Notes: </ins> <br>

<ins>1st Week Notes:</ins> <br>
- Created the "SQL and Web Server" project and GitHub repo.
- Created all HTML pages and designed with a CSS file.

<ins>2nd Week Notes:</ins> <br>
- Database connection is established.
- Six tables along with necessary columns and data are entered.
- Tested the database data calling and inserting.
- All assignment requirements are completed using the Console App.

<ins>Parner Individual Notes : </ins> <br>
<ins>**William**</ins><br>
N/A
<br><br>
<ins>**Kyle**</ins><br>
N/A

## Branching
No branching is created.

## Testing
No Unit Test files are created as the nature of the project. Manual testing 
are performed in each step of code improvements.

# Time Expenditures:
<pre>Assignment 9: Predicted Hours: 20h		Actual Hours:	24h		 </pre>

The actual hours recorded on top reflect the time spent with the partner to complete the 
assignment. It excludes time spent reading and understanding the assignment instructions 
at the beginning of the assignment. It also excludes times spent individually if there are any.
See below for partners' notes.

<ins> Time Tracking Notes : </ins> <br>
<ins>1st Week:</ins> <br>
 - Used times for the project went efficiently. All hours put into the project came out with results. 

In the first week, a total of 8 hours were spent with the partner to work on this project.

<ins>2nd Week:</ins> <br>
- The completed jobs this week did not take that much time. However,
the part we could not complete, which being able to communicate with the
the local server took so much time to figure out.

In the second week, a total of 16 hrs were spent with the partner to work on this project.

<ins>**William**</ins><br>
N/A
<br><br>
<ins>**Kyle**</ins><br>
N/A <br>

<em>Final Comments:</em> We spent more time on establishing a connection with the database using JavaScript and 
establishing a communication with the local host/server.

# Comments to Evaluators:

The assignment's key requirement points are explained below. <br>

At the beginning of the project, first, we created HTML as pages first and thought
we could call them by C# and manipulate data. However, as the professor mentioned 
in class, that would be a very time-consuming and difficult job to do. We experienced that
difficulity giving it a change and trying to make it work like that (as html pages rather than sending and
receiving the html tags as string through communicating by C# code). Therefore, as of now, we still
working on incorporating our HTML pages.

We spent fine amount of time connecting the database using JavaScript but we were unsucessfull.
We sought resources online, but could not find a solution for JavaScript connecting SSMS. All
of our trials went unsucessful.

We built beautiful and fully functioning HTML pages although we would not incorporate them
with the localhost as of now. To test them, simply find the index.html file. It's located
in the "html" folder. Open it in a browser. Thats all. You should be able to navigate 
to all other pages from there as we built links between them. They may not show the
data published from the database. However, if you could look at them and evaluate 
the "html" part of the project based on those pages, that would be wonderful.

As of now, we completed all parts of the projects using the Console App. We could not
figure out communicate with the local host. If we could have figured that out, it would be an easy task
for us to send all the HTML we already created and manipulate data.

To show our understanding of the database part of the project, we completed the tasks using the
Console App as I mentioned above. To test that, please edit the variables on top and run the
Console App. You will see the data you enter. It will be inserted into the database as well as a table
you give a name will be created with columns (two columns). More details about each section of the 
project are discussed below.

**Insert Into Database End Point:**<br>
Data entered is expected to be in the form of http://localhost:11001/scores/[name]/[highmass]/[gameid]/[winnerplayerid]/endtime]/[endtime]/[TimeSizeReached850X850InMiliiSec] .
(This will work only if the local communication part will be finished in our project. As of now, we did not finish
that part, but we may be able to finish by the time we submit the project).

The inserted data will be entered into the "Games" table.

**"Your Choice" part of the assignment** <br>
We chose to pull the maximum number of players eaten top 3 games with game IDs.
It will print GameID and The number of players eaten (3 of them, ordered by descending).
This information is stored in the GameState table. Hence, data is pulled from this table.

**"Create A Table" part of the assignment**<br>
First, a table creation will be attempted. If the table already exists under the same name, 
it will return an error. In this case, try again changing the table name. In the second step, 
using insertDataIntoTheNewlyCreatedTableInDatabase() method, desired data can be entered( in practice, this
will be done together with the table creation as we receive table names and information to store in
that table from the user. So you may enter table tame and information to store at the same time).

There will be two columns entered. The data types of both columns are varchar(255) so the data will be
expected to be entered in this datatype.
All three of the data, table name, column1 name, and column2 name have to be entered to 
successfully create the table.

Table name, column1, and column2 names can be entered using the variables defined on top. You will
just need to change the values of those variables.

To seed data into that table, use insertDataIntoTheNewlyCreatedTableInDatabase() method (The program use this
method, nothing to do on the users' side besides providing data to enter).

**"Insert Data Into Newly Created Table" part of the assignment**<br>
Once a table is created, using insertDataIntoTheNewlyCreatedTableInDatabase() method, new data can be seeded.
There are two string-type columns.
Data can be changed by editing the string variables on top of the program page, Program.cs.

It would be possible to make the created table has more columns and different data types than string.
However, for the sake of easiness in testing, we just chose two column tables in creating and those columns
to be in a string format.


All HTML pages have a ".html" extension.

It's possible to navigate to all other pages from any single page. They are linked to each other.

<em>All Available pages are listed below:</em><br>
- index.html: Landing/Home page. It's possible to navigate to all other pages.
- create.html: Creates and seeds the database
- fancy.html: Our "fancy" choice will be performed through this page.
- highScores.html: Publishes high scores from the database.
- notFound.html: Takes to a page where it says "Page is not found".
- score4Particular.html: Created to show a particular player's data.

<em>SCascading Style Sheets (CSS) page</em><br>
- style.css: Styles all HTML files. Located in the "css" folder.<br>

Additional/Non-project related page/s:
- contact.html

**Instrumenting your Client part of the assignment**<br>
We implemented Webserver project into the Agario game. It stores all the data defined in the 
"Games" table ("PlayerName(varchar(50)), "HighMass"(int), GameID"(int), "WinnerPlayerID"(int), 
"StartTime"(datetime), "EndTime"(datetime), TimeSizeReached850X850InMiliiSec(varchar(50))).

To sucessfully store the data, game may have to be played until the end, (for example, until the player dies).
We have had times the GUI didn't store data when we exited from the game.

To test the GUIClient saving data, first, open the instructor's "WindowsServer". Second,
launch the GUIClinet. Play the same. Check your database ("Games" table) in the end with your name.

There is a way to grasp messages/data from the server without needing the game project. However, since we 
could not figure that out, we decided to catch those data through the GUIClient.

Please build the GUIClient first otherwise there may be some gliching issue.
Then whole solution should be built. Referencing is also must. necessary SQL packaging
may also be installed first into your GUIClient from NuGet before sucessfully running the game.
Once all packaging and referencing is done, The game should successfully launch as we test it
multiple times.

We appreciate your hard work. 
Thank you for evaluating our project and providing feedback for us. <br>

Have a wonderful day!

# Assignment Specific Topics
The "SQL and Web Server" solution can be summarized in three parts: storing data in a database,
pulling data from the database, and publishing data in a Web browser.

# Consulted Peers:
N/A

# Examples of Good Software Practice (GSP)
<pre><ins>DRY</ins> :</pre>
DRY is an abbreviation of "Don't repeat yourself". It's a principle of Software Engineering that
has the goal of reducing repetition and redundancy in the coding. Using abstractions and normalization
are advised over redundancy <a href="https://en.wikipedia.org/wiki/Don%27t_repeat_yourself">[4]</a>.

<pre><ins>Separation of Concerns</ins> :</pre>
This concept is similar to the "divide and conquer" principle where you divide
a big software project into small projects to complete. A software design technique that focuses on separating 
and freeing functionalities of a program is called Modular programming. Making each of the divided small 
projects independent and addressing a separate concern, it'll make it easy to reduce, detect 
and fix the errors. <a href="https://en.wikipedia.org/wiki/Separation_of_concerns">[5]</a>

<pre><ins>Good Code Typing Practices</ins> :</pre>
Good coding practices can be listed as: Naming variables with a relevant name, commenting 
in between code lines with a brief explanation if the code is not self-explanatory, creating 
helper methods that can be used multiple times and by other sections.


<pre><ins>Testing Strategies</ins> :</pre>
Unit Testing can be summarized in 3 types of techniques:<br>

1. <ins>Black Box Testing : </ins> In this testing, input, user interface, and output parts are covered.
2. <ins>White Box Testing : </ins> In this testing, functionality, design structure, and code models are covered.
3. <ins>Gray Box Testing : </ins> In this testing, analysis of code performance, relevant test cases,
methods, and functions are covered.<a href="https://www.geeksforgeeks.org/unit-testing-software-testing/">[6]</a>


# References:
1. Canvas Page Class Materials.(For example, lecture slides, additional resources and pdf files). <br>
2. Piazza website that is linked to the course on the Canvas Page. <br>
3. https://learn.microsoft.com/en-us/dotnet/maui/what-is-maui?view=net-maui-7.0 <br>
4. https://en.wikipedia.org/wiki/Don%27t_repeat_yourself<br>
5. https://en.wikipedia.org/wiki/Separation_of_concerns<br>
6. https://www.geeksforgeeks.org/unit-testing-software-testing/<br>
7. https://learn.microsoft.com/en-us/sql/ssms/download-sql-server-management-studio-ssms?view=sql-server-ver16<br>
8. https://en.wikipedia.org/wiki/CSS<br><br>





