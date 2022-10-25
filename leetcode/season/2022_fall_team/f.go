package main

import (
	"fmt"
	"strings"
)

var dss = [2][]struct{ x, y int }{{{-1, 0}, {0, 1}}, {{1, 0}, {0, -1}}}

func reservoir(a []string) (ans int) {
	n, m := len(a), len(a[0])

	for _, s := range a {
		s = strings.ReplaceAll(s, "l", "\\")
		s = strings.ReplaceAll(s, "r", "/")
		//s = strings.ReplaceAll(s, ".", " ")
		fmt.Println(s)
	}

	for _, s := range a {
		s0 := ""
		s1 := ""
		for _, c := range s {
			if c == 'l' {
				s0 += "\\ "
				s1 += " \\"
			} else if c == 'r' {
				s0 += " /"
				s1 += "/ "
			} else {
				s0 += "  "
				s1 += "  "
			}
		}
		//s = strings.ReplaceAll(s, "l", "\\")
		//s = strings.ReplaceAll(s, "r", "/")
		//s = strings.ReplaceAll(s, ".", " ")
		fmt.Println(s0)
		fmt.Println(s1)
	}

	// 0 上 1 下
	//vis := make([][][2]bool, n)
	//for i := range vis {
	//	vis[i] = make([][2]bool, m)
	//}

	wt := make([][][2]bool, n)
	for i := range wt {
		wt[i] = make([][2]bool, m)
	}

	// v = (r,c) + (r,c+1)
	// 只能走 r <= lim 的
	//
	dfs := func(r, c, lim int) (touchLR bool, touchUD bool, vis [][][2]bool) {
		vis = make([][][2]bool, n)
		for i := range vis {
			vis[i] = make([][2]bool, m)
		}
		//vis[r][c][0] = true
		//vis[r][c+1][0] = true

		//if r == 3 {
		//	println()
		//}

		var f func(int, int, int)
		f = func(x, y, p int) {
			if vis[x][y][p] {
				return
			}
			vis[x][y][p] = true
			cur := a[x][y]

			// 上
			if p == 0 {
				if x > lim {
					b := a[x-1][y]
					if b == '.' {
						f(x-1, y, 0)
						f(x-1, y, 1)
					} else {
						f(x-1, y, 1)
					}
				}
				if x == 0 {
					touchUD = true
				}
			}

			// 下
			if p == 1 {
				if x+1 < n {
					b := a[x+1][y]
					if b == '.' {
						f(x+1, y, 0)
						f(x+1, y, 1)
					} else {
						f(x+1, y, 0)
					}
				} else {
					touchUD = true
				}
			}

			// 左
			if y > 0 {
				if cur == '.' || p == 0 == (cur == 'r') {
					b := a[x][y-1]
					if b == '.' {
						f(x, y-1, 0)
						f(x, y-1, 1)
					} else if b == 'l' {
						f(x, y-1, 0)
					} else {
						f(x, y-1, 1)
					}
				}
			} else {
				if cur == '.' || p == 0 == (cur == 'r') {
					touchLR = true
				}
			}

			// 右
			if y+1 < m {
				if cur == '.' || p == 0 == (cur == 'l') {
					b := a[x][y+1]
					if b == '.' {
						f(x, y+1, 0)
						f(x, y+1, 1)
					} else if b == 'r' {
						f(x, y+1, 0)
					} else {
						f(x, y+1, 1)
					}
				}
			} else {
				if cur == '.' || p == 0 == (cur == 'l') {
					touchLR = true
				}
			}

		}
		f(r, c, 0)
		f(r, c+1, 0)

		//for len(q) > 0 {
		//	tmp := q
		//	q = nil
		//	for _, p := range tmp {
		//		wt[p.x][p.y][p.p] = true
		//		dirs := dss[p.p]
		//		if p.p == 0 {
		//			x, y := p.x-1, p.y
		//			if 0 <= x && x < n && 0 <= y && y < m && !wt[x][y][1] {
		//				q = append(q, pair{x, y})
		//			}
		//		}
		//		for _, d := range dirs {
		//			if x, y := p.x+d.x, p.y+d.y; 0 <= x && x < n && 0 <= y && y < m && !wt[x][y][p.p^1] {
		//				dis[x][y] = step
		//				q = append(q, pair{x, y})
		//			}
		//		}
		//	}
		//}
		return
	}

	for i, r := range a {
		for j, v := range r {
			if v == 'l' && j+1 < m && r[j+1] == 'r' {
				//if !wt[i][j][0] {
				var tmp [][][2]bool
				lim := i
				for ; lim >= 0; lim-- {
					touchLR, touchUD, vv := dfs(i, j, lim)
					if touchLR {
						break
					}
					tmp = vv
					if touchUD {
						break
					}
				}
				if lim < 0 {
					fmt.Println(i, j, "skip")
					continue
				}
				cnt := 0
				for i, r := range tmp {
					for j, v := range r {
						if v[0] {
							wt[i][j][0] = true
							cnt++
						}
						if v[1] {
							wt[i][j][1] = true
							cnt++
						}
					}
				}
				fmt.Println(i, j, cnt)
				//}
			}
		}
	}

	for _, r := range wt {
		for _, v := range r {
			if v[0] {
				ans++
			}
			if v[1] {
				ans++
			}
		}
	}

	return
}
