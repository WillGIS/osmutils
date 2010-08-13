// gcc -Wall `xml2-config --cflags --libs` -lproj -o shp2osm dbfopen.c shpopen.c osm.c shape.c shp2osm.c

CC=gcc
CFLAGS=-Wall `xml2-config --cflags --libs`

all: osm2shp shp2osm

shp2osm: dbfopen.c shpopen.c osm.c shape.c shp2osm.c $(CC) $(CFLAGS) -o $@

osm2shp: osm2shp.c $(CC) $(CFLAGS) -o $@
