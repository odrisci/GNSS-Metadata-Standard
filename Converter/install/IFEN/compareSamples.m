clear all;
close all;

fpt=fopen( 'RoofTop_FE0_Band0.stream', 'rb' );
sampt=fread( fpt, 1000, 'bit2' );
fclose( fpt );
sampt=2*sampt+1;

fp=fopen( 'L1.dat', 'rb' );
samp = fread( fp, 1000, 'int8' );
fclose( fp );


plot( sampt, samp, '.-b' );
hold on; grid on;


fpt=fopen( 'RoofTop_FE0_Band1.stream', 'rb' );
sampt=fread( fpt, 1000, 'bit2' );
fclose( fpt );
sampt=2*sampt+1;

fp=fopen( 'L2.dat', 'rb' );
samp = fread( fp, 1000, 'int8' );
fclose( fp );


plot( sampt, samp, '.-r' );
