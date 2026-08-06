component {

     function processForms(required struct formData) {
         if (formData.keyExists('isbn13') && formData.isbn13.len() == 13 && formData.title.len() > 0) {
             if (formData.keyExists('uploadImage') && formData.uploadImage.len() > 0) {
                 formData.image = uploadBookCover();
             }
 
             if (formData.keyExists('genre')) {
                 deleteAllBookGenres(formData.isbn13);
 
                 formData.genre
                     .listToArray()
                     .each(function(item) {
                         insertGenre(item, formData.isbn13);
                     });
             }
 
             var qs = new query(datasource = application.dsource);
             qs.setSQL('
                IF NOT EXISTS( SELECT * FROM books WHERE isbn13=:isbn13)
                   INSERT INTO books (isbn13,title) VALUES (:isbn13,:title);
                UPDATE books SET
                    title=:title,
                    weight=:weight,
                    year=:year,
                    pages=:pages,
                    publisher=:publisher,
                    image=:image,
                    description=:description
                     WHERE isbn13=:isbn13
                ');
             qs.addparam(
                 name = 'isbn13',
                 cfsqltype = 'CF_SQL_NVARCHAR',
                 value = formData.isbn13,
                 nullValue = formData.isbn13.len() != 13
             );
             qs.addparam(
                 name = 'title',
                 cfsqltype = 'CF_SQL_NVARCHAR',
                 value = formData.title,
                 nullValue = formData.title.len() == 0
             );
             qs.addParam(name = 'weight', CFSQLTYPE = 'CF_SQL_NUMERIC', value = formData.weight);
             qs.addParam(name = 'year', CFSQLTYPE = 'CF_SQL_NUMERIC', value = formData.year);
             qs.addParam(name = 'pages', CFSQLTYPE = 'CF_SQL_NUMERIC', value = formData.pages);
             qs.addParam(name = 'publisher', CFSQLTYPE = 'CF_SQL_NVARCHAR', value = formData.publisher);
             qs.addParam(name = 'image', CFSQLTYPE = 'CF_SQL_NVARCHAR', value = formData.image);
             qs.addParam(name = 'description', CFSQLTYPE = 'CF_SQL_NVARCHAR', value = formData.description);
             qs.execute();
         }
     }
 
     function deleteAllBookGenres(isbn13) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('delete genresToBooks Where isbn13=:isbn13');
         qs.addParam(name = 'isbn13', value = arguments.isbn13);
         return qs.execute().getResult();
     }
 
     function insertGenre(genreid, isbn13) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('INSERT
                INTO genresToBooks (genreid, isbn13)
                VALUES (:genreid, :isbn13)');
         qs.addParam(name = 'isbn13', value = arguments.isbn13);
         qs.addParam(name = 'genreid', value = arguments.genreid);
         qs.execute();
     }
 
     function uploadBookCover() {
         var imageData = fileUpload(
             expandPath('../images/'),
             'uploadImage',
             '*',
             'makeUnique'
         );
 
         return imageData.serverFile;
     }
 
 
     function allBooks(qterm) {
         if (qterm.len() == 0) {
             return queryNew('title');
         } else {
             var qs = new query(datasource = application.dsource);
             qs.setSql('select * from books where title like :qterm order by title');
             qs.addParam(name = 'qterm', value = '%#qterm#%');
             return qs.execute().getResult();
         }
     }
 
     function bookDetails(isbn13) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('select * from books where isbn13=:isbn13');
         qs.addParam(name = 'isbn13', CFSQLTYPE = 'CF_SQL_NVARCHAR', value = arguments.isbn13);
         return qs.execute().getResult();
     }
 
     function allPublishers(isbn13) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('select * from publishers order by name');
         return qs.execute().getResult();
     }
 
     function allGenres() {
         var qs = new query(datasource = application.dsource);
         qs.setSql('select * from genres order by genreName');
         return qs.execute().getResult();
     }
 
     function bookGenres(book) {
         var qs = new query(datasource = application.dsource);
         qs.setSql('Select * FROM genresToBooks
                INNER JOIN genres ON genresToBooks.genreid = genres.genreid
                WHERE genresToBooks.isbn13 = :isbn13
                ORDER by genreName');
         qs.addParam(name = 'isbn13', value = arguments.book);
         return qs.execute().getResult();
     }
 
 } 
                                 