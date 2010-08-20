CC=gcc
CFLAGS=-Wall `xml2-config --cflags --libs` -lproj

SOURCE=dbfopen.c shpopen.c keyvals.c transform.c ruleset.c osm.c shape.c shp2osm.c
OBJECTS=${SOURCE:.c=.o}
.PREFIXES = .c .o

.c.o:
	$(CC) -c $(CFLAGS) $<

shp2osm: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

all: shp2osm

clean:
	rm shp2osm *.o

install: shp2osm
