===========================
 Shp2OSM & PG2OSM
===========================
The main goal of these utilities is something that 
can pull data out of a PostGIS (postgresql) database and 
convert it to OsmChange or JOSM format for use in OpenStreetMap.  

Along with a PG2OSM utility, a Shp2OSM utility is also included.

* Shp2OSM - utility for converting shapefiles to OSM
* PG2OSM - utility for converting PostGIS data to OSM


 COMPILE
------------

gcc 
  -Wall `xml2-config --cflags --libs` -lproj 
  -o shp2osm 
  dbfopen.c shpopen.c keyvals.c transform.c osm.c shape.c shp2osm.c

 TODO
-------------
* Makefile
* ...
