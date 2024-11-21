public class FactureClient{
    public static void main(String[] args){
        if(args.length < 3){
            System.out.println("Nombre d'argument sur la ligne de commande insuffisant :");
            System.out.println("Usage : java FactureClient <prenom> <nom> <montant1> <montant2> ...<montantN>");
            return;
        }
        String prenom = args[0];
        String nom = args[1];
        double total = 0.0 ;
        for(int i =2 ; i < args.length ; i++){
            try{
                double montant = Double.parseDouble(args[i]) ;
                total += montant ;
            }catch (NumberFormatException e){
                System.out.println("Erreur :  +args["+ i +"] +  n'est pas un nombre valide .e.args[i]");
                return;
            }
        }
        System.out.println("Client :" + prenom + " " + nom);
        System.out.println("A payer par " + prenom + " " + nom + ":" + total);
        
    }

}