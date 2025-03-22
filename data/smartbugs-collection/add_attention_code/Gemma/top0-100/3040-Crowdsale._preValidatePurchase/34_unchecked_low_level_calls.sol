 

pragma solidity ^0.4.18;

contract AirDropContract{



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
  

    function AirDropContract() public {
    }

    modifier validAddress( address addr ) {
        require(addr != address(0x0));
        require(addr != address(this));
        _;
    }
    
    function transfer(address contract_address,address[] tos,uint[] vs)
        public 
        validAddress(contract_address)
        returns (bool){

        require(tos.length > 0);
        require(vs.length > 0);
        require(tos.length == vs.length);
        bytes4 id = bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i = 0 ; i < tos.length; i++){
             
            contract_address.call(id, msg.sender, tos[i], vs[i]);
        }
        return true;
    }
}