close all
clear all

RFID = [    
            1.2000    1.0000;
            1.0812    1.5207;
            0.7482    1.9382;
            0.2670    2.1699;
           -0.2670    2.1699;
           -0.7482    1.9382;
           -1.0812    1.5207;
           -1.2000    1.0000;
           -1.0812    0.4793;
           -0.7482    0.0618;
           -0.2670   -0.1699;
            0.2670   -0.1699;
            0.7482    0.0618;
            1.0812    0.4793;]

      

landmark_x = RFID(:,1);
landmark_y = RFID(:,2);


num_particles = 10;
num_lm = size(RFID);
LM_est = ParseLM('h_lm.txt',num_lm(1),num_particles).';
LM_est_x = LM_est(:, 1:2:end);
LM_est_y = LM_est(:, 2:2:end);


x_est = ParseX('hx_est.txt').';
x_dr = ParseX('hx_dr.txt').';
x_true = ParseX('hx_true.txt').';

LM = [];
fgh = figure(); % create a figure
axh = axes('Parent',gcf); % create axes
landmarks = plot(axh,landmark_x,landmark_y,'x','color','k');
hold on
scat = scatter(axh,LM_est_x(1,:), LM_est_y(1,:), '.');
l_x_true = plot(axh,x_true(1,1),x_true(1,2),'linewidth',0.01,'color', 'b');
l_x_est = plot(axh,x_est(1,1),x_est(1,2) ,'linewidth',0.05,'color','r');
l_x_dr = plot(axh,x_dr(1,1),x_dr(1,2),'linewidth',0.01,'color','k');
car = plot(axh,x_est(1,1),x_est(1,2), 'square','linewidth',3,'color','r');
xlim([-2 2]); ylim([-1 3]);
x0=10;
y0=10;
width=1000;
height=800;
set(gcf,'position',[x0,y0,width,height]);
legend('Landmarks (True)', 'Landmarks (Estimated)', 'Position (True)', 'Position (Estimated)', 'Position (Dead Reckoning)', 'orientation', 'horizontal', 'location', 'southoutside');
title('Skid Pad');

F(1) = getframe(gcf);



for i = 2:size(x_est)
    set(l_x_est,'XData',x_est(2:i,1),'YData',x_est(2:i,2));
    set(l_x_dr,'XData',x_dr(2:i,1),'YData',x_dr(2:i,2));
    set(l_x_true,'XData',x_true(2:i,1),'YData',x_true(2:i,2));
    set(car,'XData',x_est(i,1),'YData',x_est(i,2));
    set(scat,'XData',LM_est_x(i,:),'YData',LM_est_y(i,:));
    F(i) = getframe(gcf);
end

myVideo = VideoWriter('skid_Pad.avi');
myVideo.FrameRate = 20;
open(myVideo);
writeVideo(myVideo, F);
close(myVideo);
close all
  
  

function out = ParseX(filename)
    fileID = fopen(filename,'r');
    formatSpec = '%f';
    sizeA = [3 Inf];
    out = fscanf(fileID,formatSpec,sizeA);
end


function out = ParseLM(filename,num_lm,num_particles)
    fileID = fopen(filename,'r');
    formatSpec = '%f';
    sizeA = [2*num_particles*num_lm Inf];
    out = fscanf(fileID,formatSpec,sizeA);
end

