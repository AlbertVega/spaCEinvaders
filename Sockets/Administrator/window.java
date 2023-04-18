package Administrator;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;
import javax.swing.*;

public class window {
    private static JFrame Frame;
    private static JPanel MainPanel, MatrixPanel, LeftPanel;
    private static String Aliens;
    private static ArrayList<JCheckBox> CheckBoxes = new ArrayList<>();

    public window(){
        createWindow();
        createLabel();
        createMatrix();
        createButtons();
        createTextField();
    }
    private static void createWindow(){
        Frame = new JFrame("Server");
        MainPanel = new JPanel(new BorderLayout(5,5));
        Frame.setLocationRelativeTo(null);
        Frame.setVisible(true);
        Frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        Frame.setSize(750, 600);
        Frame.setResizable(false);
        MainPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
        Frame.add(MainPanel);
    }

    private static void createLabel(){
        JLabel TextLabel = new JLabel("SpaCE Invaders ADMIN", SwingConstants.CENTER);
        TextLabel.setFont(new Font("Eras Bold ITC", Font.PLAIN, 24));
        TextLabel.validate();
        MainPanel.add(TextLabel, BorderLayout.NORTH);
    }

    private static void createMatrix(){
        MatrixPanel = new JPanel(new GridLayout(5,11));
        Integer count = 0;
        for(int i=1; i<6; i++){
            for (int j=0; j<12; j++){
                CheckBoxes.add(new JCheckBox(i + "," + j));
                MatrixPanel.add(CheckBoxes.get(count));
                count++;
            }
        }
        MainPanel.add(MatrixPanel, BorderLayout.CENTER);
        MainPanel.validate();
        MainPanel.repaint();
    }

    private static void createButtons(){
        JButton Send = new JButton("SEND");
        Send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ArrayList<String> list = new ArrayList<>();
                for (Integer i=0; i<CheckBoxes.size(); i++){
                    if (CheckBoxes.get(i).isSelected()){
                        list.add(CheckBoxes.get(i).getText());
                    }
                }
                for (int i=0; i<list.size(); i++){
                    System.out.println(list.get(i) + " " + i +"\n");
                }
            }
        });
        MainPanel.add(Send, BorderLayout.SOUTH);
        MainPanel.validate();
        MainPanel.repaint();
    }

    private static void createTextField(){
        LeftPanel = new JPanel();
        JTextField SpeedField = new JTextField(3);
        LeftPanel.add(SpeedField);
        SpeedField.setBounds(10,100,50,50);
        MainPanel.add(LeftPanel, BorderLayout.WEST);
        MainPanel.validate();
        MainPanel.repaint();

    }
}