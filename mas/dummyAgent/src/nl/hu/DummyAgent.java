package nl.hu;
import java.util.Random;
import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.Behaviour;
import jade.core.behaviours.TickerBehaviour;
import jade.core.behaviours.CyclicBehaviour;
import jade.domain.DFService;
import jade.domain.FIPAException;
import jade.domain.FIPAAgentManagement.DFAgentDescription;
import jade.domain.FIPAAgentManagement.ServiceDescription;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;
import com.google.gson.Gson;
import java.io.IOException;
 
import java.io.BufferedReader; 
import java.io.IOException; 
import java.io.InputStreamReader; 
import java.util.ArrayList; 
import nl.hu.client.BlackboardClient;
import nl.hu.message.MessageBuilder;
import java.util.HashMap; 

public class DummyAgent extends Agent 
{
    private BlackboardClient client = new BlackboardClient("localhost");	
	private MessageBuilder builder = new MessageBuilder();
	private String database = "REXOS";
	private String topic = "instruction"; 
	private String collection = "blackboard";
	
	public void setup()
	{
		
		builder.add("message.payload.maxAcceleration", 5);
		try{
		//client.insert(builder.buildMessage(MessageBuilder.MessageType.GET));
		}catch(Exception e){
		    e.printStackTrace();
		}
		System.out.println("Send a message to this agent to move the DeltaRobotNode to relative points using content:");
		System.out.println("x@y@z");
		this.addBehaviour(new CyclicBehaviour()
		{
			@Override
			public void action() 
			{
				client.setDatabase(database);	
				client.setCollection(collection);

				Gson gson = new Gson();

				for(int i =0; i< 100; i++)
				{

					InstructionMessage a = new InstructionMessage("moveRelativePoint", "DeltaRobotNode", "FIND_ID", null ,new Point(i,0,0,50));
					BlackboardMessage mes = new BlackboardMessage(topic,a);
					try
					{
						//Thread.sleep(100);
						System.out.println(gson.toJson(mes));
						client.insertJson(gson.toJson(mes));
						System.out.println("Message Added");
					}
					catch(Exception e)
					{
						e.printStackTrace();
					}


				/*
				ArrayList<Point> points = new ArrayList<Point>();
				points.add(new Point(rand(-10,10),rand(-10,10),rand(-10,10), 50));
				points.add(new Point(rand(-10,10),rand(-10,10),rand(-10,10) , 50));
				InstructionMessage a = new InstructionMessage("moveRelativePath", "DeltaRobotNode", "FIND_ID", null ,points);
				BlackboardMessage mes = new BlackboardMessage(topic,a);
				try
				{
					System.out.println(gson.toJson(mes));
					client.insertJson(gson.toJson(mes));
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}*/
					
								
				
				}
				while(true){}
			}
		});

	}



    public static int rand(int lo, int hi)
    {
    	Random randomGenerator = new Random();
            int n = hi - lo + 1;
            int i = randomGenerator.nextInt() % n;
            if (i < 0)
                    i = -i;
            return lo + i;
    }



}