Read this to lead you through installing of the module

1.Install this fboauth module

2.Create an app in facebook
  Disable sandbox mode and enable Website with Facebook Login.

3.Add the App ID and App secret from the facebook App in facebook
  here admin/config/people/fboauth

4.Set the content types, which nodes could be posted to facebook
  here admin/config/people/fboauth_post/settings
  
5.Set the permissions - go to admin/people/permissions and set 
  the "Post to facebook" permission to the role that must be able to post
  
6.Set the facebook login block that comes with fboauth module that the users
  could be able to login through facebook.
  
Note:Now the module would work with the Article content type since by default it
     contains all the needed fields for posting to facebook - those are 
     Title, Body, Image - if you want the module to work properly just add those
     fields as existing fields to the content type that yow want use.
 
