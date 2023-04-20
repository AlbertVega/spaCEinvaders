package Administrator.GUI;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.*;
import javax.swing.*;

import Administrator.Aliens.Alien;
import Administrator.Aliens.AlienFactory;
import Administrator.Players.Player1;
import Administrator.Players.Player2;
import Server.JSONBuilder;
import Server.Server;

public class window implements ActionListener{
    private static JFrame Frame;
    private static JPanel MainPanel, MatrixPanel;
    private static ArrayList<JCheckBox> CheckBoxes = new ArrayList<>();
    private Player1 Player1;
    private Player2 Player2;
    private AlienFactory AlienFactory;
    private Server Server;
    private final JSONBuilder JSONBuilder = new JSONBuilder();

    public window(Player1 player1, Player2 player2, AlienFactory alienFactory, Server server){
        this.Player1 = player1;
        this.Player2 = player2;
        this.AlienFactory = alienFactory;
        this.Server = server;
        createWindow();
        createLabel();
        createMatrix();
        createButtons();
        createTextFields();
        createPlayerFields();
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
        for(int i=0; i<5; i++){
            for (int j=0; j<11; j++){
                CheckBoxes.add(new JCheckBox(i + "," + j));
                MatrixPanel.add(CheckBoxes.get(count));
                count++;
            }
        }
        MainPanel.add(MatrixPanel, BorderLayout.CENTER);
        MainPanel.validate();
        MainPanel.repaint();
    }

    private void createButtons(){
        JButton Send = new JButton("SEND");
        Send.addActionListener(this);
        MainPanel.add(Send, BorderLayout.SOUTH);
        MainPanel.validate();
        MainPanel.repaint();
    }

    private static void createTextFields(){
        JPanel LeftPanel = new JPanel(new GridLayout(10,1));
        JTextField AliensSpeed = new JTextField(3);
        JTextField OvnisSpeed = new JTextField(3);
        JLabel SpeedLabel = new JLabel("Aliens Speed");
        JLabel OvnisLabel = new JLabel("Ovnis Speed");        
        
        LeftPanel.add(SpeedLabel);
        LeftPanel.add(AliensSpeed);
        LeftPanel.add(OvnisLabel);
        LeftPanel.add(OvnisSpeed);       
        MainPanel.add(LeftPanel, BorderLayout.WEST);
        MainPanel.validate();
        MainPanel.repaint();
    }

    private void createPlayerFields(){
        JPanel RightPanel = new JPanel(new GridLayout(15,1));
        JLabel Player1Label = new JLabel("Player 1");
        JLabel Player2Label = new JLabel("Player 2");
        JLabel Player1Life = new JLabel("Life: " + Player1.getLife());
        JLabel Player2Life = new JLabel("Life: " + Player2.getLife());
        JLabel Player1Score = new JLabel("Score: " + Player1.getScore());
        JLabel Player2Score = new JLabel("Score: " + Player2.getScore());
        RightPanel.add(Player1Label);
        RightPanel.add(Player1Score);
        RightPanel.add(Player1Life);        
        RightPanel.add(Player2Label);
        RightPanel.add(Player2Score);
        RightPanel.add(Player2Life);
        MainPanel.add(RightPanel, BorderLayout.EAST);
        MainPanel.revalidate();
        MainPanel.repaint();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        ArrayList<Alien> AlienList = new ArrayList<>();
        Integer count = 0;

        for (int i=0; i<CheckBoxes.size(); i++){

            if (CheckBoxes.get(i).isSelected() && i<11){ 
                AlienList.add(AlienFactory.createAlien("Calamar", "Calamar" + count));
                String[] Positions = CheckBoxes.get(i).getText().split(",");
                AlienList.get(count).setXPos(Integer.valueOf(Positions[0]));
                AlienList.get(count).setYPos(Integer.valueOf(Positions[1]));
                count++;

            }else if (CheckBoxes.get(i).isSelected() && 10<i && i<22){ 
                AlienList.add(AlienFactory.createAlien("Cangrejo", "Cangrejo" + count));
                String[] Positions = CheckBoxes.get(i).getText().split(",");
                AlienList.get(count).setXPos(Integer.valueOf(Positions[0]));
                AlienList.get(count).setYPos(Integer.valueOf(Positions[1]));
                count++;

            }else if (CheckBoxes.get(i).isSelected() && 21<i && i<33){ 
                AlienList.add(AlienFactory.createAlien("Cangrejo", "Cangrejo" + count));
                String[] Positions = CheckBoxes.get(i).getText().split(",");
                AlienList.get(count).setXPos(Integer.valueOf(Positions[0]));
                AlienList.get(count).setYPos(Integer.valueOf(Positions[1]));
                count++;
            }else if (CheckBoxes.get(i).isSelected() && 32<i && i<44){ 
                AlienList.add(AlienFactory.createAlien("Pulpo", "Pulpo" + count));
                String[] Positions = CheckBoxes.get(i).getText().split(",");
                AlienList.get(count).setXPos(Integer.valueOf(Positions[0]));
                AlienList.get(count).setYPos(Integer.valueOf(Positions[1]));
                count++;
            }else if (CheckBoxes.get(i).isSelected() && 43<i && i<55){ 
                AlienList.add(AlienFactory.createAlien("Pulpo", "Pulpo" + count));
                String[] Positions = CheckBoxes.get(i).getText().split(",");
                AlienList.get(count).setXPos(Integer.valueOf(Positions[0]));
                AlienList.get(count).setYPos(Integer.valueOf(Positions[1]));
                count++;
            }
        }
        for (int i=0; i<AlienList.size(); i++){
            try {
                String Respuesta = JSONBuilder.createAlien(AlienList.get(i).getName(), AlienList.get(i).getXPos(), AlienList.get(i).getYPos());
                Server.Response(Respuesta);

            } catch (IOException ex) {
                ex.printStackTrace();           
            }
            //enviar Pos, tipo de alien, speed general.
        }        
    }
}