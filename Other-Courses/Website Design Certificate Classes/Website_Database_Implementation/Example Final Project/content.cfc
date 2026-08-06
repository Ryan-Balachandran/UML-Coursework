component {

     function processForms( formData ){
         var qs = new query(datasource=application.dsource);
         qs.setSql("
             if not exists( select * from content where id=:id)
                 insert into content (title,description,dateWritten)
                 values (:title,:description,:dateWritten);
             update content set 
                 title=:title,
                 description = :description
                 where id=:id");
         qs.addParam(name="id",value=form.id);
         qs.addParam(name="title",value=form.title);
         qs.addParam(name="description",value=form.description);
         qs.addParam(name="dateWritten",value=dateformat(now(), "yyyy-mm-dd"));
         qs.execute();
     }
 
     function allArticles( ){
         var qs = new query(datasource=application.dsource);
         qs.setSql("select * from content order by title");
         return qs.execute().getResult();
     }
 
 
     function obtainArticle( id ){
         var qs = new query(datasource=application.dsource);
         qs.setSql("select * from content where id=:id");
         qs.addParam(name="id",value=arguments.id);
         return qs.execute().getResult();
     }
 } 