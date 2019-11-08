function checkUser(){
  firebase.auth().onAuthStateChanged(function(user) {
    if (user) {
      if(user != null){
        var user = firebase.auth().currentUser;
        console.log(user);
        window.location.replace("menu.html");
        console.log(user.displayName);

      }

    } else {
      // window.location.replace("login.html");
    }
  });
}

checkUser();
setTimeout(function(){
  
console.log("asd");
addContent();
// logout();

$("#loginBtn").click(function(){
  login();
});

function addContent(){
  var code = `
      <header class="position-fixed " style="width: 100%; z-index: 999;">
	<nav id="navigasi" class="navbar p-1 navbar-expand-lg navbar-light bg-transparent">
		<div class="col-4" style="margin-left: auto;">
			<a class="navbar-brand white" href="index.html"><b class="white"><i class="fa fa-lock"></i> C-Lock</b></a>
		</div>
		<div class="col-4" style="margin-right: auto;">
			<a class="navbar-item white float-right m-1" href="#"></a>
			<a class="navbar-item white float-right m-1 ml-5" style="color: black" href="login.html"><u>Login</u></a>
		</div>
	</nav>
</header>
<main>
  <section class="home-banner-area">
      <div class="pt-180" style="margin-bottom: 100px">
        <div class="card col-3 p-3" style="margin-left: auto; margin-right:auto;">
          <label>Email</label>
          <input type="text" placeholder="Email" id="email" name="email">
          <label>Password</label>
          <input type="password" placeholder="Password" id="password" name="password">

          <div class="center">
            <button id="loginBtn" class="btn-login p-1 mt-3">Login</button>
          </div>
        </div>
      </div>
      
  </section>
</main>
<!-- Footer -->
<footer class="page-footer font-small blue pt-4">

  <!-- Footer Links -->
  <div class="container-fluid text-center text-md-left">

    <!-- Grid row -->
    <div class="row">

      <!-- Grid column -->
      <div class="col-md-6 mt-md-0 mt-3">

        <!-- Content -->
        <h5 class="text-uppercase font-mont" style="color:white;">Tentang</h5>
        <p class="font-mont" style="color:white;">Ini merupakan project IOT yang digunakan untuk sarana belajar mengajar</p>

      </div>
      <!-- Grid column -->

      <hr class="clearfix w-100 d-md-none pb-3">

      <!-- Grid column -->
      <div class="col-md-6 mt-md-0 mt-3">

        <!-- Content -->
        <h5 class="text-uppercase font-mont" style="color:white;">Kontak</h5>
        <p class="font-mont" style="color:white;"><i class="fas fa-phone"></i> : 08123145689</p>
        <p class="font-mont" style="color:white;"><i class="fas fa-envelope"></i> : c-lock@clock.company.com</p>
        <p class="font-mont" style="color:white;"><i class="fas fa-link"></i> : www.clock-company.com</p>
      </div>
    </div>
    <!-- Grid row -->

  </div>
  <!-- Footer Links -->

  <!-- Copyright -->
  <div class="footer-copyright text-center py-3">&copy; 2019 Copyright:
    <a href=""> C-Lock</a>
  </div>
  <!-- Copyright -->

</footer>
<!-- Footer -->
      `;
$('#content').html(code);
};
}, 500);
function login(){

  var userEmail = $("#email").val();
  var userPass = $("#password").val();

  firebase.auth().signInWithEmailAndPassword(userEmail, userPass).catch(function(error) {

    var errorCode = error.code;
    var errorMessage = error.message;

    window.alert("Error : " + errorMessage);
  });

}