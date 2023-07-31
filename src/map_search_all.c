/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_search_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:01:27 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/31 20:03:23 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	stack_init(t_stack *stack)
{
	stack->head = 0;
	stack->tail = -1;
}

void enstack(t_stack *stack, t_cie *cie)
{
	if((stack->tail + 2) % (vars.map_x + 1) == stack->head)
		return ;///////キューが満杯でENQUEUEできません\n");
	
	stack->data[(stack->tail + 1) % (vars.map_x + 1)] = *cie;
	stack->tail = (stack->tail + 1) % (vars.map_x + 1);
}

t_cie *dequeue(t_stack *stack)
{
	t_cie *ret;

	/* キューが空なら何もせずに関数終了 */
	if((stack->tail + 1) % (vars.map_x + 1) == stack->head)
	{
		printf("キューが空です\n");
		return (NULL);
	}
	/* データの先頭からデータを取得 */
	ret = &(stack->data[stack->head]);
	/* データの先頭を１つ後ろにずらす */
	stack->head = (stack->head + 1) % QUEUE_SIZE;
	/* 取得したデータを返却 */
	return (ret);
}

/* ゴールまでの経路を出力する関数 */
void printRoute(int num_trace)
{
	int n;
	int count = 0;
	int	m;

	/* ゴールからスタートまでの経路をrouteに格納 */
	
	/* 最後に通過したノードの情報のtrace上の位置 */
	n = num_trace - 1;
	while (true)
	{
		t_cie pos = trace[n]; /* 通過したノードの情報を取得 */
		route[count] = pos; /* 通過したノードを覚えておく */
		count++;
		if (pos.b_i == -1)
			break;
		m = n - 1;
		while (m >= 0)
		{
			/* posの前に通過したノードの情報が格納されているtrace上の位置を探索 */
			if (trace[m].i == pos.b_i)
			{
				/* posの前に通過した位置はtrace[m]に格納されている */
				n = m;
				break;
			}
			m--;
		}
	}
	
	/* ゴールからスタートまでの経路を逆順に表示 */
	m = count - 1;
	for (m >= 0)
	{
	    printf("%d,", route[m].i);
		m--;
	}
	printf("\n\n");
}

/* スタートからゴールを探索する関数*/
bool	search(int s_i, int g_i)
{
	t_cie	pos;
	int		num_trace;
	bool	ret;

	pos.i = s_i;
	pos.b_i = -1;
	enqueue(&queue, &pos); /* キューにノードの情報を格納*/
	num_trace = 0;
	
	while (true)
	{
		int i;
	
		/* キューから次の探索候補のノードを取得*/
		POS_T *next = dequeue(&queue);
		if (next == NULL)
		{
			/* 次の探索候補がない場合は探索失敗 */
			ret = false;
			break;
		}
		/* 探索するノードの座標を取得 */
		i = next->i;
		/* 探索するノードを探索済のノードとして覚えておく */
		trace[num_trace] = *next;
		num_trace++;
		if (i == g_i)
		{
			/* 探索対象が見つかったので探索成功 */
			printf("ゴールに到着\n");
			printRoute(num_trace);
			ret = true;
			break;
		}
		/* 探索済みのノードに印をつける */
		searched[i] = 1;
		for (int e = 0; e < MAX_EDGE; e++)
		{
			if (graph[i][e] != -1)
			{
				if (searched[graph[i][e]] != 1)
				{
					pos.i = graph[i][e];
					pos.b_i = i;
					enqueue(&queue, &pos);
				}
			}
		}
	}
	return (ret);
}


//static int	check(t_vars vars, int i, int j)
//{
//	if (i >= vars.map_y || j >= vars.map_x
//		|| vars.map[i][j] == WALL || vars.map[i][j] == PASSED)
//			return (0);
//	return (1);
//}
//
//static int	search(t_vars vars, int s_i, int s_j)
//{
//	t_cie	cie;
//	int		i;
//	int		j;
//
//	if (check(s_i, s_j) == 1)
//		error();
//	else
//		vars.map[s_i][s_j] = PASSED;
//	while (1)
//	{
//	}
//	return (0);
//}

void	map_search_all(char **argv, t_vars vars)
{
	t_player	player;

	vars = import_map(argv, vars);
	vars = set_null(vars);
	player = search_player(vars);
	stack_init(&queue);
	/* スタートの位置を0、ゴールの位置を10として開始 */
	if (search())
		printf("ゴールが見つかりました！\n");
	else
		printf("NOゴール！\n");
	all_free(vars.map);
//	error();
}
