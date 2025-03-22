 

 pragma solidity ^0.4.15;

 

contract EtherLotto {

     
    uint constant TICKET_AMOUNT = 10;

     
    uint constant FEE_AMOUNT = 1;

     
    address public bank;

     
    uint public pot;

     

 
    string internal _orderString = "趙客縵胡纓吳鉤霜雪明銀鞍照白馬颯沓如流星十步殺一人千里不留行事了拂衣去深藏身與名閑過信陵飲脫劍膝前橫將炙啖朱亥持觴勸侯嬴三杯吐然諾五嶽倒為輕眼花耳熱後意氣素霓生救趙揮金槌邯鄲先震驚千秋二壯士煊赫大梁城縱死俠骨香不慚世上英誰能書閣下白首太玄經";
    
    function getOrderString () view external returns(string) {
        return _orderString;
    }

    function EtherLotto() {
        bank = msg.sender;
    }

     
     
    function play() payable {

         
        assert(msg.value == TICKET_AMOUNT);

         
        pot += msg.value;

         
         
        var random = uint(sha3(block.timestamp)) % 2;

         
        if (random == 0) {

             
            bank.transfer(FEE_AMOUNT);

             
            msg.sender.transfer(pot - FEE_AMOUNT);

             
            pot = 0;
        }
    }

}
