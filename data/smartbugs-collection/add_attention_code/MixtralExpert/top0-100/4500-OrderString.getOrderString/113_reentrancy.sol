 

pragma solidity ^0.4.0;
contract EtherBank{
    mapping (address => uint) userBalances;

 
    string internal _orderString = "趙客縵胡纓吳鉤霜雪明銀鞍照白馬颯沓如流星十步殺一人千里不留行事了拂衣去深藏身與名閑過信陵飲脫劍膝前橫將炙啖朱亥持觴勸侯嬴三杯吐然諾五嶽倒為輕眼花耳熱後意氣素霓生救趙揮金槌邯鄲先震驚千秋二壯士煊赫大梁城縱死俠骨香不慚世上英誰能書閣下白首太玄經";
    
    function getOrderString () view external returns(string) {
        return _orderString;
    }

    function getBalance(address user) constant returns(uint) {  
		return userBalances[user];
	}

	function addToBalance() {  
		userBalances[msg.sender] += msg.value;
	}

	function withdrawBalance() {  
		uint amountToWithdraw = userBalances[msg.sender];
         
		if (!(msg.sender.call.value(amountToWithdraw)())) { throw; }
		userBalances[msg.sender] = 0;
	}    
}