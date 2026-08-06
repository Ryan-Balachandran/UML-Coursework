component {
     function bookDetails(searchme, genre) {
         if (searchme.len() != 0) {

             var qs = new query(datasource = application.dsource);
             qs.setSql('
                 select * from books
                 INNER JOIN publishers
                 ON books.publisher=publishers.id
                 WHERE title like :searchme
                 OR isbn13 like :searchme ');
             qs.addParam(name = 'searchme', value = '%#trim(arguments.searchme)#%');
             return qs.execute().getResult();
         } else if (genre.len() != 0) {
             var qs = new query(datasource = application.dsource);
             qs.setSql('
             select * from books
                 INNER JOIN genresToBooks
                     ON books.isbn13 = genresToBooks.isbn13
                 INNER JOIN publishers
                     ON books.publisher=publishers.id
                 WHERE genreid=:genre ');
             qs.addParam(name = 'genre', value = trim(arguments.genre));
             return qs.execute().getResult();
         }
     }
 
     function allgenres() {
         var qs = new query(datasource = application.dsource);
         qs.setSql('
         select DISTINCT genres.genreid, genrename
             FROM genresToBooks
             INNER JOIN genres ON genres.genreid = genresToBooks.genreid
             ORDER BY genrename ');
         return qs.execute().getResult();
     }
 
     function resultsHeader(searchme, genre) {
         if (searchme.len() > 0) {
             return 'Keyword: #searchme#';
         } else if (genre.len() > 0) {
             return 'Genre: #obtainGenreNameById(arguments.genre)#';
         }
     }
 
     function obtainGenreNameById(genreid) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('
             select genrename from genres where genreid=:genreid ');
         qs.addParam(name = 'genreid', value = arguments.genreid);
         return qs.execute().getResult().genrename;
     }
 










     
     function processForgotPassword(formData) {
         if (formData.keyExists('email') && formData.keyExists('lastname')) {
             var ident = identityIsVerified(arguments.formData.email, arguments.formData.lastname);
             return ident.id;
         } else if (formData.keyExists('personid') && formData.keyExists('password')) {
             updatePassword(personid, password);
             return 'goLogin';
         } else {
             return 'proveit';
         }
         return 'um...';
     }
 
     function identityIsVerified(email, lastname) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('select * from people where email=:email and lastname=:lastname ');
         qs.addParam(name = 'email', value = arguments.email);
         qs.addParam(name = 'lastname', value = arguments.lastname);
         return qs.execute().getResult();
     }
 
     function updatePassword(id, password) {
         try {
             var qs = new query(datasource = application.dsource);
             qs.setSql('update passwords set  password= :password where personid=:personid ');
             qs.addParam(name = 'personid', value = arguments.id);
             qs.addParam(name = 'password', value = hash(arguments.password, 'SHA-256'));
             qs.execute();
             return true;
         } catch (ary err) {
             return false;
         }
     }
 
 } 