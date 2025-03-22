 

pragma solidity ^0.4.19;

contract PRIVATE_ETH_CELL
{
    mapping (address=>uint256) public balances;   
   
    uint public MinSum;
    
    LogFile Log;
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        require(!intitalized);
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        require(!intitalized);
        Log = LogFile(_log);
    }
    
    function Initialized()
    public
    {
        intitalized = true;
    }
    
    function Deposit()
    public
    payable
    {
        balances[msg.sender]+= msg.value;
        Log.AddMessage(msg.sender,msg.value,"Put");
    }
    
    function Collect(uint _am)
    public
    payable
    {
        if(balances[msg.sender]>=MinSum && balances[msg.sender]>=_am)
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                Log.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }
    
    function() 
    public 
    payable
    {
        Deposit();
    }
    
}



contract LogFile
{
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }
    
    Message[] public History;
    
    Message LastMsg;
    

    using SafeERC20 for ERC20;
    using SafeMath for uint;
    
    uint256 public constant HOLDING_START = 1533916800;
    ERC20 public tosToken = ERC20(0xFb5a551374B656C6e39787B1D3A03fEAb7f3a98E);
    
    mapping (address => uint256) public lockBalanceOf;
    mapping (address => uint256) public principalsRecords;
    mapping (address => uint256) public rewards;

    uint256 public totalLockPrincipal = 0;
    uint256 public totalLockAmount = 0;

    bool public isReward = false;

    function lock(uint256 lockAmount) public {

        require(lockAmount > 1 * 10 ** 18);
        require(now <= HOLDING_START); 

        uint256 reward = lockAmount.mul(20).div(100);

        require(reward <= (tosToken.balanceOf(this).sub(totalLockAmount)));
        tosToken.safeTransferFrom(msg.sender, this, lockAmount);

        lockBalanceOf[msg.sender] = lockBalanceOf[msg.sender].add(lockAmount).add(reward);
        principalsRecords[msg.sender] = principalsRecords[msg.sender].add(lockAmount);
        rewards[msg.sender] = rewards[msg.sender].add(reward);
        totalLockPrincipal = totalLockPrincipal.add(lockAmount);
        totalLockAmount = totalLockAmount.add(lockAmount).add(reward);

        if (totalLockPrincipal >= 5000000 * 10 ** 18) {
            isReward = true;
        }
    }

    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}