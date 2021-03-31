# hw2_version2
Created on 110.3.31

# Q1: How to setup and run your program？
A1:
1.(Inputs) 我將3個按鈕分別與電阻串聯，再將這三組並聯，接在麵包板上，再接線到板子上的3.3V的高電位pin腳
2.(Display) 開啟 uLCD.cpp 檔，先打上標頭檔(header)，利用if(某button輸入==1)的判斷式來決定按鈕是否被按下。若被按下，則分別執行指令：在按下代表Confirm的按鈕之後(將暫存的y值正式存到代表mode的x值中)，使mode的值向上加1(若已達到最大值5則保持不變)或向下減1(若已達到最小值1則保持不變)，在選擇過程中會隨著目前所選到的mode在螢幕上顯示出GUI條(條數對應到mode值)，並且提示此mode會產生出的三角波頻率，如果恰好是mode 3時會提示此頻率為RC的截止頻率，而mode 1及mode 2的生成頻率比截止頻率還小；mode 4及mode 5的生成頻率比截止頻率還大。當按下Confirm的按鈕時，除了將此時之mode值放入x值而使得板子立刻產生出新頻率的三角波(從Picoscope可觀察出)，也會在uLCD螢幕上顯示出 "Confirm!"的字樣。(由於這個部分需要一直執行判斷(一直等待輸入訊號)，因此為了防止main()主函式中的其他程式影響使得無法一直偵測輸入訊號，因此我使用Thread的方式來平行處理)。
3.(Generate waveform) 生成的三角波是由lab_3的4.5節的sawtooth波改寫而來：我將變動的i值的上升或下降幅度改變：由於我的學號108060018計算出來的結果為1+0+8+0+6+0+0+1+8 (mod 10) ≡ 23 (mod 10) ≡ 3 (mod 10)，所以我的三角波的頂端尖端(peak)位置必須在十分之三處(一個先上升後下降的波的peak左右兩側時間/長度比例為3:7)，而我將一個週期分成200等分，前60等分(佔十分之三)拿來使訊號以sawtooth的模式上升至3V，後面140等分(佔十分之七)則拿來使訊號以sawtooth的模式下降回0V，因此變動的i值總共要從0.0以60步上升至1.0左右，所以每次跳躍的間隔為1/60(約為0.016667)，另外由於輸出的參考電壓(reference voltage)為3.3V，因此若i值為1會使得輸出值為3.3V，但我們只希望最高電壓為3.0V，因此將i值乘以3/3.3，即約0.91，讓輸出的aout值最高約為3.0V；而第二個迴圈中變動的i值總共要從1.0以140步下降至0.0左右，所以每次跳躍的間隔為1/140(約為0.007143)。再來要決定每次sawtooth的小小上升/下降所需要耗費的時間：由按鈕設定好並確認(Confirm)後的頻率可計算出週期T(= 1÷頻率)，又由於我將一個週期分成200份來做sawtooth模式的上升和下降，因此sawtooth中的變動i值每變換值一次的時間為T/200秒，再轉換成毫秒(ms)即可(因為ThisThread::sleep_for()函式並不能輸入小數，為了使精準度提高，所以用ms)。
    接著我將生成的三角波訊號透過D7的pin腳傳出板子外的電路，再將其以串聯方式連接兩個電阻(電阻值為4.7kΩ)以及一個特大電容(電容值4.7μF)，最後接地(ground)，形成一個RC電路(低頻濾波器)。其截止頻率(Cut-off frequency)值由參考網站可計算出為1/[2π × (4.7k × 2) × 4.7μ]，約為0.36Hz(再另外取兩個比0.36Hz小、兩個比0.36Hz大的頻率而形成上述的5個modes)。
5.(Measure) 將連接Picoscope的線路接到此RC電路上以測量電壓值的變化：將A port連接到RC過濾後的波測量其電壓值(即連接到較後面的電阻和電容之間)；B port則連接到D7的pin腳所輸出的三角形波，測量RC電路過濾前的波。接著開啟Picoscope軟體，設定mode後即可觀察其所偵測到的波形。
6.(Sample)


# Q2: What are the results？
A2: The screenshots of Picoscope and the matlab-plots are in the folder named "For hand-in 1100331".
In the screenshots of Picoscope, the orange line is the wave before filting, and the blue line is the wave detected after RC filter, thus we compare the blue wave with the plot of matplotlib, and find out that they look almost the same.
The plots of the five modes after FFT are provided in the same folder.
