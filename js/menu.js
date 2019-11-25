$(document).ready(function() {
	checkUser();
	function checkUser(){
		  firebase.auth().onAuthStateChanged(function(user) {
		    if (user) {
		      if(user != null){
		       
		      }

		    } else {
		      window.location.replace("login.html");
		    }
		  });
		}



	setTimeout(function(){
    console.log("terpanggil");
    // writeUserData();
    // function writeUserData(){
    //   let userRef = firebase.database().ref($('#ruangan').val())
    //   userRef.child()).set(
    //     {
    //       'firstName':"handi", 
    //       'lastName': "hermawan", 
    //       'gender': "pria"
    //     }
    //   );
	// }
	
		let table = `
		<table class="table">
			<thead>
				<tr>
				<th scope="col">#</th>
				<th scope="col">Peminjam</th>
				<th scope="col">Status</th>
				<th scope="col">Deskripsi</th>
				<th scope="col">Pinjam</th>
				</tr>
			</thead>
			<tbody>
				<tr>
					<th scope="row">Sesi 1</th>
					<td id="s1-nama">-</td>
					<td id="s1-status">-</td>
					<td id="s1-desc">-</td>
					<td id="s1-button"><button class="btn-pinjam data" data-toggle="modal" data-target="#exampleModal" data-value="sesi1">Pinjam</button></td>
					<!-- <th scope="row">Sesi 1</th>
					<td>Pak Kuncoro - IOT</td>
					<td class="green bold">Terpinjam</td>
					<td>Belum Masuk</td>
					<td>-</td> -->
				</tr>
				<tr>
					<th scope="row">Sesi 2</th>
					<td id="s2-nama">-</td>
					<td id="s2-status">-</td>
					<td id="s2-desc">-</td>
					<td id="s2-button"><button class="btn-pinjam data" data-toggle="modal" data-target="#exampleModal" data-value="sesi2">Pinjam</button></td>
				</tr>
				<tr>
					<th scope="row">Sesi 3</th>
					<td id="s3-nama">-</td>
					<td id="s3-status">-</td>
					<td id="s3-desc">-</td>
					<td id="s3-button"><button class="btn-pinjam data" data-toggle="modal" data-target="#exampleModal" data-value="sesi3">Pinjam</button></td>
				</tr>
			</tbody>
			</table>
			`;
	
		var code = `
		<header class="position-fixed " style="width: 100%; z-index: 999;">
	<nav id="navigasi" class="navbar navbar-bg p-1 navbar-expand-lg navbar-light bg-transparent">
		<div class="col-4" style="margin-left: auto;">
			<a class="navbar-brand white" href="index.html"><b class="white"><i class="fa fa-lock"></i> C-Lock</b></a>
		</div>
		<div class="col-4" style="margin-right: auto;">
			<a class="navbar-item white float-right m-1" href="#"></a>
			<a class="navbar-item white float-right m-1 ml-5" style="color: black;" id="logoutBtn"><u>Logout</u></a>
		</div>
	</nav>
</header>
<main>
<br><br><br>
  <section class="m-4 ">
	<div class="card col-3 p-3 mb-3">	
   		<span>Selamat Datang <span id="nama_pengguna"></span></span>
	</div>
	<div class="card col-12 p-3">
		<div>
			<select name="ruangan" id="ruangan">
				<option value="" disabled selected>Ruangan</option>
				<option value="a">LAB A</option>
				<option value="b">LAB B</option>
				<option value="c">LAB C</option>
				<option value="d">LAB D</option>
				<option value="e">LAB E</option>
			</select>
			<input type="date" id="date" disabled>
		</div>
	
		<div class="col-12 mt-3" id="table-content">
			
		</div>
	</div>
  </section>

  <div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
	<div class="modal-dialog" role="document">
	  <div class="modal-content">
		<div class="modal-header">
		  <h5 class="modal-title" id="exampleModalLabel">New message</h5>
		  <button type="button" id="btn_modal_close" class="close" data-dismiss="modal" aria-label="Close">
			<span aria-hidden="true">&times;</span>
		  </button>
		</div>
		<div class="modal-body">
		  <form>
			<div class="form-group">
			  <label for="message-text" class="col-form-label">Keterangan peminjaman:</label>
			  <textarea class="form-control" id="message-text"></textarea>
			</div>
		  </form>
		</div>
		<div class="modal-footer">
		  <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
		  <button type="button" id="sendBtn" class="btn btn-primary">Send message</button>
		</div>
	  </div>
	</div>
  </div>

    <div class="modal fade" id="deleteModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
	<div class="modal-dialog" role="document">
	  <div class="modal-content">
		<div class="modal-header">
		  <h5 class="modal-title" id="exampleModalLabel">New message</h5>
		  <button type="button" id="btn_modal_delete_close" class="close" data-dismiss="modal" aria-label="Close">
			<span aria-hidden="true">&times;</span>
		  </button>
		</div>
		<div class="modal-body">
		  <form>
			<div class="form-group">
			  <label for="message-text" class="col-form-label">Apakah anda yakin akan menghapus jadwal ?</label>
			</div>
		  </form>
		</div>
		<div class="modal-footer">
		  <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
		  <button type="button" id="deleteBtn" class="btn btn-primary" style="background-color: red;">Hapus</button>
		</div>
	  </div>
	</div>
  </div>

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
`;

	$("#menu").html(code);
	$("#logoutBtn").click(function(){
		console.log("clicked");
		logout();
		checkUser();
		var user = firebase.auth().currentUser;
			console.log(user);
			console.log(user.displayName);
			alert("hai")
	});

	function logout(){
		firebase.auth().signOut();
	}

		
	let sesi = 0;
	let day;
	let month;
	let year;
	var user = firebase.auth().currentUser;
	console.log(user);
	console.log(user.displayName);
	$(".data").attr("data-user", user.displayName);
	$("#nama_pengguna").html(user.displayName);
	$('#exampleModal').on('show.bs.modal', function (event) {
		var button = $(event.relatedTarget) 
		var recipient = button.data('user')
		sesi = $(event.relatedTarget).data('value');
				console.log(sesi);
		var modal = $(this)
		var ruangan = $('#ruangan').val();
		modal.find('.modal-title').text('Peminjaman Lab ' + ruangan.toUpperCase())
		modal.find('.modal-body input').val(recipient)
	});

	$('#deleteModal').on('show.bs.modal', function (event) {
		var button = $(event.relatedTarget) 
		var recipient = button.data('user')
		sesi = $(event.relatedTarget).data('value');
		console.log(sesi);
		var modal = $(this)
		var ruangan = $('#ruangan').val();
		modal.find('.modal-title').text('Peminjaman Lab ' + ruangan.toUpperCase())
		modal.find('.modal-body input').val(recipient)
	});


	$('#ruangan').change(function(){
		console.log("berubah");
		$('#date').removeAttr("disabled");
	});

	function uuidv4() {
	  return ([1e7]+-1e3+-4e3+-8e3+-1e11).replace(/[018]/g, c =>
	    (c ^ crypto.getRandomValues(new Uint8Array(1))[0] & 15 >> c / 4).toString(16)
	  );
	}

	$('#sendBtn').click(function(){
	let userRef = firebase.database().ref("Booking/"+year+""+month+""+day)
	let usr = firebase.auth().currentUser
	let randomToken = uuidv4()
	let end = 0
	let start = 0

		if(sesi=="sesi1"){
			start = "7.30";
			end = "10.30";
		}else if (sesi=="sesi2"){
			start = "10.30";
			end = "13.30";
		}else{
			start = "13.30";
			end = "16.30";
		}

      userRef.child(randomToken).set(
        {
        	'description':  $('#message-text').val(),
			'jamEnd': end, 
			'jamStart': start, 
			'lab': $('#ruangan').val(),
			'name': usr.displayName, 
			'rid': randomToken,
			'status': "0",
			'uid':usr.uid,
			'waktu': sesi
        }
	  );
	  
	  $('#btn_modal_close').click();
	});

	$('#deleteBtn').click(function(){
		console.log("deleted")
		let userRef = firebase.database().ref("Booking/"+year+""+month+""+day+"/"+sesi);
		userRef.remove();
		$('#btn_modal_delete_close').click();
		var date = new Date($('#date').val());
		day = date.getDate();
		month = date.getMonth() + 1;
		year = date.getFullYear();
		$("#table-content").html(table);
		var db_path="Booking/"+year+""+month+""+day;
			var leadsRef = firebase.database().ref(db_path);
			console.log(db_path);
			leadsRef.on('value', function(snapshot) {
				snapshot.forEach(function(childSnapshot) {
					var childData = childSnapshot.val();
					console.log(childData);
					console.log(childData.waktu);
					if($('#ruangan').val()==childData.lab){
						if(childData.waktu=="sesi1"){
							console.log("masuk sesi 1")
							$('#s1-nama').html(childData.name);
							$('#s1-desc').html(childData.description);
							$('#s1-status').html(childData.status);
							if(user.uid==childData.uid)
								$('#s1-button').html(`<button class="btn-hapus data" id="del-sesi1" data-toggle="modal" data-target="#deleteModal" data-value="sesi1">Hapus</button>`);
							else
								$('#s1-button').html('');
						}else if(childData.waktu=="sesi2"){
							$('#s2-nama').html(childData.name);
							$('#s2-desc').html(childData.description);
							$('#s2-status').html(childData.status);
							if(user.uid==childData.uid)
								$('#s2-button').html(`<button class="btn-hapus data" id="del-sesi2" data-toggle="modal" data-target="#deleteModal" data-value="sesi2">Hapus</button>`);
							else
								$('#s2-button').html('');
						}else if(childData.waktu=="sesi3"){
							$('#s3-nama').html(childData.name);
							$('#s3-desc').html(childData.description);
							$('#s3-status').html(childData.status);
							if(user.uid==childData.uid)
								$('#s3-button').html(`<button class="btn-hapus data" id="del-sesi3" data-toggle="modal" data-target="#deleteModal" data-value="sesi3">Hapus</button>`);
							else
								$('#s3-button').html('');
						}
					}
				}); 
			});

	});

	

	$('#date').change(function(){

		$("#table-content").html(table);
		var date = new Date($('#date').val());
		day = date.getDate();
		month = date.getMonth() + 1;
		year = date.getFullYear();
		if(date.getDay() == 6 || date.getDay() == 0) {
			alert('Tidak bisa memilih hari sabtu atau minggu!');
			$('#date').val("");
			$("#table-content").html("");
		}else{
			console.log("Ada");
			var db_path="Booking/"+year+""+month+""+day;
			var leadsRef = firebase.database().ref(db_path);
			console.log(db_path);
			leadsRef.on('value', function(snapshot) {
				snapshot.forEach(function(childSnapshot) {
					var childData = childSnapshot.val();
					console.log(childData);
					console.log(childData.waktu);
					if($('#ruangan').val()==childData.lab){
						if(childData.waktu=="sesi1"){
							console.log("masuk sesi 1")
							$('#s1-nama').html(childData.name);
							$('#s1-desc').html(childData.description);
							$('#s1-status').html(childData.status);
							if(user.uid==childData.uid)
								$('#s1-button').html(`<button class="btn-hapus data" id="del-sesi1" data-toggle="modal" data-target="#deleteModal" data-value=`+childData.rid+`>Hapus</button>`);
							else
								$('#s1-button').html('');
						}else if(childData.waktu=="sesi2"){
							$('#s2-nama').html(childData.name);
							$('#s2-desc').html(childData.description);
							$('#s2-status').html(childData.status);
							if(user.uid==childData.uid)
								$('#s2-button').html(`<button class="btn-hapus data" id="del-sesi2" data-toggle="modal" data-target="#deleteModal" data-value=`+childData.rid+`>Hapus</button>`);
							else
								$('#s2-button').html('');
						}else if(childData.waktu=="sesi3"){
							$('#s3-nama').html(childData.name);
							$('#s3-desc').html(childData.description);
							$('#s3-status').html(childData.status);
							if(user.uid==childData.uid)
								$('#s3-button').html(`<button class="btn-hapus data" id="del-sesi3" data-toggle="modal" data-target="#deleteModal" data-value=`+childData.rid+`>Hapus</button>`);
							else
								$('#s3-button').html('');
						}
					}
				}); 
			});

			// tampilkan table pada web setelah ada date
			
		}
	})

	}, 1000);
});