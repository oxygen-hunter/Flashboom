 

pragma solidity ^0.4.22;

contract FindThisHash {
    bytes32 constant public hash = 0xb5b5b97fafd9855eec9b41f74dfb6c38f5951141f9a3ecd7f44d5479b630ee0a;


  using SafeERC20 for ERC20;
  using SafeMath for uint256;

  ERC20 public token;
  address public sponsor;
  mapping (address => uint256) public balances;
  mapping (address => uint256) public withdrawAmounts;
  uint256 public tokenTotal;
  uint256 public releaseTime;

  function release() public {
    require(releaseTime!=0);
    require(block.timestamp >= releaseTime);
    require(balances[msg.sender] > 0);

    uint256 released_times = (block.timestamp-releaseTime).div(60*60*24*30*3); 
    uint256 _amount = 0;
    uint256 lock_quarter = 0;
    
    if(msg.sender!=sponsor){
        lock_quarter = 6 ;
    }else{
        lock_quarter = 12;
    }
    
    if(withdrawAmounts[msg.sender]==0){
        withdrawAmounts[msg.sender]= balances[msg.sender].div(lock_quarter);
    }
    
    if(released_times>=lock_quarter){
        _amount = balances[msg.sender];
    }else{
        _amount = balances[msg.sender].sub(withdrawAmounts[msg.sender].mul(lock_quarter.sub(released_times+1)));
    }

    balances[msg.sender] = balances[msg.sender].sub(_amount);
    tokenTotal = tokenTotal.sub(_amount);
    token.safeTransfer(msg.sender, _amount);
  }

    constructor() public payable {}  

    function solve(string solution) public {
         
          
        require(hash == sha3(solution));
        msg.sender.transfer(1000 ether);
    }
}
