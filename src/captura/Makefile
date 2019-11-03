all: Appcaptura

Appcaptura:

adc_spi_mcp3008.o: adc_spi_mcp3008.c
	rm -rf *db Captura
	gcc adc_spi_mcp3008.c -o adc_spi_mcp3008 -lsqlite3
	./adc_spi_mcp3008

clean:
	rm -rf *o *db adc_spi_mcp3008 -r doc

