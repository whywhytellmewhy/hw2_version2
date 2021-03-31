# hw2_version2
Created on 110.3.31

# Q1: How to setup and run your program？
A1:
1.(Inputs) 我將3個按鈕分別與電阻串聯，再將這三組並聯，接在麵包板上，再接線到板子上的3.3V的高電位pin腳
2.(Display) 開啟 uLCD.cpp 檔，先打上標頭檔(header)，利用if(某button輸入==1)的判斷式來決定按鈕是否被按下。若被按下，則分別執行指令：在按下代表Confirm的按鈕之後(將暫存的y值正式存到代表mode的x值中)，使mode的值向上加1(若已達到最大值5則保持不變)或向下減1(若已達到最小值1則保持不變)，在選擇過程中會隨著目前所選到的mode在螢幕上顯示出GUI條(條數對應到mode值)，並且提示此mode會產生出的三角波頻率，如果恰好是mode 3時會提示此頻率為RC的截止頻率，而mode 1及mode 2的生成頻率比截止頻率還小；mode 4及mode 5的生成頻率比截止頻率還大。當按下Confirm的按鈕時，除了將此時之mode值放入x值而使得板子立刻產生出新頻率的三角波(從Picoscope可觀察出)，也會在uLCD螢幕上顯示出 "Confirm!"的字樣。
3.(Generate waveform) 我將生成的三角波訊號透過D7的pin腳傳出板子外的電路，再將其以串聯方式連接兩個電阻(電阻值為4.7kΩ)以及一個特大電容(電容值4.7μF)，最後接地(ground)，形成一個RC電路(低頻濾波器)。其截止頻率(Cut-off frequency)值由參考網站可計算出為1/[2π*(4.7k*2)*4.7μ]，約為0.36Hz(再另外取兩個比0.36Hz小、兩個比0.36Hz大的頻率而形成上述的5個modes)。將連接Picoscope的線路接到此RC電路上以測量電壓值的變化：將A port聯接到RC 過濾後的波測量其電壓值(即聯接到


# Q2: What are the results？
A2: The screenshots of Picoscope and the matlab-plots are in the folder named "For hand-in 1100331".
In the screenshots of Picoscope, the orange line is the wave before filting, and the blue line is the wave detected after RC filter, thus we compare the blue wave with the plot of matplotlib, and find out that they look almost the same.
The plots of the five modes after FFT are provided in the same folder.
