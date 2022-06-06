<h1>sokoscape-Game</h1>

In this Repository, you can find 3 stages of a C project that I had to create during my 2nd year of Bachelor Degree.
The purpose of this small project was to create a video game using the SDL library in C.

<h2>First Step:</h2> 

In this step, we don't have much functionality, as we tried to install the SDL library on Ubuntu (this is the most annoying part of the project).
Then, when we succeed to install it, we had to make a map of tiles which correspond to our textures (that our teacher gave us)

You can see an example of the map below:

<p align="center">
  <img width="500px" src='https://user-images.githubusercontent.com/106914120/172068177-d7bd6403-5385-4262-805c-2568840a40be.png'><br>
  map that we had to rebuild
</p>



<h2>Second Step:</h2> 

So now, we had a constraint : Create the map via an extern file 

As you can see, we haven't yet character's control or even character's collisions.

We could find in the extern file used to create the map some information as :

<div align="center">

| FUNCTION | NAME |
| --- | --- |
| The path of our textures (floor and object) | **TUILE** or **OBJET** |
| The height (number of tiles) | **HAUTEUR** |
| The width (number of tiles)   | **LARGEUR** |
| A number map in which each number fit with a texture | **TAB** |
| The number of object | **NBOBJET** |
| The player with his position | **JOUEUR** |
| The weapon of our character | **ARME** |
| And in the final step we will have the hitbox of every textures | **HITBOX** |
</div>

You can see an example of an extern file (the names seen before are really important, else the program doesn't work)

<table align="center" border=0>
  <tr>
    <td><img height ="500px" src ='https://user-images.githubusercontent.com/106914120/172077252-95b98ca4-729b-4716-9bf7-6958af511994.png'></td>
    <td><img height ="500px" src ='https://user-images.githubusercontent.com/106914120/172077280-7b9ee999-a4fb-49d4-afe5-806ee5fa956e.png'></td>
    <td><img height ="500px" src ='https://user-images.githubusercontent.com/106914120/172077283-99e4bbc1-b15b-4acd-9fc6-1ef6d3ec04ff.png'></td>
  </tr>
</table>

I have to say that, we were able and allow to add as many features that we want (so I added a weapon and more that you will see further)

<h2> Final Step </h2>
Obviously, in this part we will add many features :
<div align="center">

| CONSTRAINT | BONUS |
| --- | --- |
| Show the floor | Add weapon which makes damage |
| Show our character | add more life |
| Show informations (time of the run for example)   | Add animation of sliding |
| Collect keyboard information | Add ranking system |
| Calculate the new objects' positions | Add sound and music |
|  | Possibility to enter our nickname |
|  | Message either when we win either when we die |

  
<p align="center">
  <img width="500px" src='https://user-images.githubusercontent.com/106914120/172079232-e5ba5db6-d2b0-4f5a-b882-be432d5a9a5f.png'><br>
  Final map
</p>
  
<br><br>
  
<p>If you download this program, you could find some problems. Indeed, there is a memory leak (I think due to the display of textures) that we close automatically at a moment. Moreover, we didn't have a lot of time to make this project (1 week per step) and by the way I'm a student. If you have questions or suggestions or even corrections, don't hesitate.</p>
