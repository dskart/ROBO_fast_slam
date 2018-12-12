
close all
clear all

RFID = [10.0,  -2.0;
          15.0,  10.0;
          15.0,  15.0;
          10.0,  20.0;
          3.0,   15.0;
          -5.0,  20.0;
          -5.0,  5.0;
          -10.0, 15.0];

landmark_x = RFID(:,1);
landmark_y = RFID(:,2);

fgh = figure(); % create a figure
axh = axes('Parent',fgh); % create axes

landmarks = plot(axh,landmark_x,landmark_y,'x','color','k');
hold on

num_particles = 10;
num_lm = size(RFID);
LM_est = ParseLM('h_lm.txt',num_lm(1),num_particles).';

x_est = ParseX('hx_est.txt').';
x_dr = ParseX('hx_dr.txt').';
x_true = ParseX('hx_true.txt').';

LM = [];
for i = 1:num_particles
    LM(:,i,:) = 
        
end
l_LM_est = plot(axh,landmark_x,landmark_y,'x','color','b');
l_x_est = plot(axh,x_est(1,1),x_est(1,2) ,'linewidth',0.01,'color','r');
l_x_dr = plot(axh,x_dr(1,1),x_dr(1,2),'linewidth',0.01,'color','k');
l_x_true = plot(axh,x_true(1,1),x_true(1,2),'linewidth',0.01,'color', 'b');
car = plot(axh,x_est(1,1),x_est(1,2), 'square','linewidth',3,'color','r');

for i = 2:size(x_est)
    set(l_x_est,'XData',x_est(2:i,1),'YData',x_est(2:i,2))
    set(l_x_dr,'XData',x_dr(2:i,1),'YData',x_dr(2:i,2))
    set(l_x_true,'XData',x_true(2:i,1),'YData',x_true(2:i,2))
    set(car,'XData',x_est(i,1),'YData',x_est(i,2))

%     plot(axhx_est(i,1),x_est(i,2), 'square','linewidth',1,'color','r')
    
    pause(0.05)
end


  

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
function out = ParseParticles(filename)
end
